#ifndef EXPRESSION_TPP
#define EXPRESSION_TPP

// Implémentation de Analyseur<P>.
// Inclus par src/Expression.cpp (compilé dans libpile.so) et, si besoin,
// par un programme client qui utilise une autre classe de pile P.

#include <sstream>
#include "Expression.h"

template <template <typename> class P>
Resultat Analyseur<P>::verifier(const std::string& expr) {
    std::vector<Token> tokens;
    try {
        tokens = decouper(expr);
    } catch (const ErreurExpression& e) {
        return {false, e.what(), e.position};
    }
    if (tokens.empty())
        return {false, "Expression vide", 0};

    P<Token> delimiteurs;
    bool attendOperande = true;   // état de l'automate

    for (const Token& t : tokens) {
        switch (t.type) {
            case NOMBRE:
            case VARIABLE:
                if (!attendOperande)
                    return {false, "Operande '" + t.texte + "' inattendu (operateur manquant)", t.position};
                attendOperande = false;
                break;

            case OPERATEUR:
                if (attendOperande)
                    return {false, "Operateur '" + t.texte + "' inattendu (operande manquant)", t.position};
                attendOperande = true;
                break;

            case OUVRANTE:
                if (!attendOperande)
                    return {false, "'" + t.texte + "' inattendu (operateur manquant)", t.position};
                if (!delimiteurs.estVide()
                    && rangDelimiteur(t.texte[0]) > rangDelimiteur(delimiteurs.getSommet().texte[0]))
                    return {false, "Ordre non respecte : '" + t.texte + "' a l'interieur de '"
                                   + delimiteurs.getSommet().texte + "'", t.position};
                delimiteurs.empiler(t);
                break;

            case FERMANTE: {
                if (delimiteurs.estVide())
                    return {false, "'" + t.texte + "' sans delimiteur ouvrant", t.position};
                if (attendOperande)
                    return {false, "Operande manquant avant '" + t.texte + "'", t.position};
                Token ouvrant = delimiteurs.depiler();
                if (ouvrant.texte[0] != ouvranteAssociee(t.texte[0]))
                    return {false, "'" + t.texte + "' ne ferme pas '" + ouvrant.texte
                                   + "' (position " + std::to_string(ouvrant.position) + ")", t.position};
                break;
            }
        }
    }

    if (!delimiteurs.estVide()) {
        const Token& ouvrant = delimiteurs.getSommet();
        return {false, "'" + ouvrant.texte + "' jamais ferme", ouvrant.position};
    }
    if (attendOperande)
        return {false, "Expression incomplete (operande manquant a la fin)", tokens.back().position};

    return {true, "Expression valide", -1};
}

template <template <typename> class P>
template <typename V>
V Analyseur<P>::parcourirInfixe(const std::string& expr,
                                std::function<V(const Token&)> feuille,
                                std::function<V(char, const V&, const V&)> combiner) {
    Resultat r = verifier(expr);
    if (!r.valide)
        throw ErreurExpression(r.message, r.position);

    P<char> operateurs;
    P<V> valeurs;

    // dépile un opérateur et ses deux opérandes, empile le résultat
    auto reduire = [&]() {
        char op = operateurs.depiler();
        V b = valeurs.depiler();
        V a = valeurs.depiler();
        valeurs.empiler(combiner(op, a, b));
    };

    for (const Token& t : decouper(expr)) {
        switch (t.type) {
            case NOMBRE:
            case VARIABLE:
                valeurs.empiler(feuille(t));
                break;
            case OUVRANTE:
                operateurs.empiler(t.texte[0]);
                break;
            case FERMANTE:
                while (!estOuvrante(operateurs.getSommet()))
                    reduire();
                operateurs.depiler();   // retire le délimiteur ouvrant
                break;
            case OPERATEUR: {
                char op = t.texte[0];
                while (!operateurs.estVide() && estOperateur(operateurs.getSommet())) {
                    char haut = operateurs.getSommet();
                    if (priorite(haut) > priorite(op)
                        || (priorite(haut) == priorite(op) && !associatifDroite(op)))
                        reduire();
                    else
                        break;
                }
                operateurs.empiler(op);
                break;
            }
        }
    }
    while (!operateurs.estVide())
        reduire();
    return valeurs.depiler();
}

template <template <typename> class P>
double Analyseur<P>::evaluer(const std::string& expr) {
    return parcourirInfixe<double>(expr,
        [](const Token& t) -> double {
            if (t.type == VARIABLE)
                throw std::invalid_argument("Variable '" + t.texte + "' non evaluable");
            return std::stod(t.texte);
        },
        [](char op, const double& a, const double& b) { return appliquer(op, a, b); });
}

template <template <typename> class P>
std::string Analyseur<P>::versPrefixe(const std::string& expr) {
    return parcourirInfixe<std::string>(expr,
        [](const Token& t) { return t.texte; },
        [](char op, const std::string& a, const std::string& b) {
            return std::string(1, op) + " " + a + " " + b;
        });
}

template <template <typename> class P>
std::string Analyseur<P>::versPostfixe(const std::string& expr) {
    return parcourirInfixe<std::string>(expr,
        [](const Token& t) { return t.texte; },
        [](char op, const std::string& a, const std::string& b) {
            return a + " " + b + " " + std::string(1, op);
        });
}

template <template <typename> class P>
template <typename V>
V Analyseur<P>::parcourirPrefixe(const std::string& prefixe,
                                 std::function<V(const std::string&)> feuille,
                                 std::function<V(char, const V&, const V&)> combiner) {
    std::vector<std::string> jetons;
    std::istringstream is(prefixe);
    std::string j;
    while (is >> j)
        jetons.push_back(j);
    if (jetons.empty())
        throw std::invalid_argument("Expression prefixe vide");

    P<V> valeurs;
    for (int i = (int)jetons.size() - 1; i >= 0; i--) {
        const std::string& s = jetons[i];
        if (s.size() == 1 && estOperateur(s[0])) {
            if (valeurs.taille() < 2)
                throw std::invalid_argument("Operandes manquants pour '" + s + "'");
            V a = valeurs.depiler();   // premier opérande
            V b = valeurs.depiler();   // second opérande
            valeurs.empiler(combiner(s[0], a, b));
        } else if (estNombre(s) || estIdentificateur(s)) {
            valeurs.empiler(feuille(s));
        } else {
            throw std::invalid_argument("Jeton invalide '" + s + "'");
        }
    }
    if (valeurs.taille() != 1)
        throw std::invalid_argument("Trop d'operandes (operateur manquant)");
    return valeurs.depiler();
}

template <template <typename> class P>
std::string Analyseur<P>::prefixeVersInfixe(const std::string& prefixe) {
    std::string s = parcourirPrefixe<std::string>(prefixe,
        [](const std::string& o) { return o; },
        [](char op, const std::string& a, const std::string& b) {
            return "(" + a + " " + std::string(1, op) + " " + b + ")";
        });
    // les parenthèses extérieures sont superflues
    if (s.size() > 1 && s.front() == '(' && s.back() == ')')
        s = s.substr(1, s.size() - 2);
    return s;
}

template <template <typename> class P>
double Analyseur<P>::evaluerPrefixe(const std::string& prefixe) {
    return parcourirPrefixe<double>(prefixe,
        [](const std::string& o) -> double {
            if (!estNombre(o))
                throw std::invalid_argument("Variable '" + o + "' non evaluable");
            return std::stod(o);
        },
        [](char op, const double& a, const double& b) { return appliquer(op, a, b); });
}

#endif
