#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "Pile.h"
#include "PileListe.h"
#include "PileTableau.h"

// ---------------------------------------------------------------------------
// Analyse lexicale : découpage d'une expression infixe en jetons (tokens)
// ---------------------------------------------------------------------------

enum TypeToken { NOMBRE, VARIABLE, OPERATEUR, OUVRANTE, FERMANTE };

struct Token {
    TypeToken type;
    std::string texte;
    int position;   // indice du premier caractère dans l'expression
};

std::ostream& operator<<(std::ostream& os, const Token& t);

// Erreur de syntaxe localisée dans l'expression
class ErreurExpression : public std::invalid_argument {
public:
    int position;
    ErreurExpression(const std::string& msg, int pos)
        : std::invalid_argument(msg), position(pos) {}
};

// Résultat de la vérification d'une expression
struct Resultat {
    bool valide;
    std::string message;
    int position;   // position de l'erreur, -1 si l'expression est valide
};

// Fonctions utilitaires (définies dans src/Expression.cpp -> libpile.so)
bool estOuvrante(char c);
bool estFermante(char c);
bool estOperateur(char c);
char ouvranteAssociee(char fermante);

// Hiérarchie des délimiteurs : { [ ( ) ] }
// un délimiteur ne peut contenir que des délimiteurs de rang inférieur ou égal
int rangDelimiteur(char c);

int priorite(char op);

// a ^ b ^ c = a ^ (b ^ c) ; les autres opérateurs sont associatifs à gauche
bool associatifDroite(char op);

std::vector<Token> decouper(const std::string& expr);
bool estNombre(const std::string& s);
bool estIdentificateur(const std::string& s);
double appliquer(char op, double a, double b);

// ---------------------------------------------------------------------------
// Analyseur générique : P est la classe de pile utilisée
// (PileTableau ou PileListe). Tous les algorithmes reposent uniquement
// sur l'interface Pile<T>. Le code est dans Expression.tpp.
// ---------------------------------------------------------------------------

template <template <typename> class P>
class Analyseur {
public:
    // Vérifie la validité d'une expression infixe :
    //  1. caractères autorisés ;
    //  2. délimiteurs équilibrés et bien appariés ;
    //  3. ordre des délimiteurs { [ ( ) ] } respecté ;
    //  4. alternance opérande / opérateur correcte.
    static Resultat verifier(const std::string& expr);

    // Parcours générique d'une expression infixe valide avec deux piles
    // (algorithme de Dijkstra) : une pile d'opérateurs, une pile de valeurs.
    // - feuille   : transforme un opérande en valeur de type V
    // - combiner  : construit la valeur de "a op b"
    // Selon V et combiner, on obtient l'évaluation, la forme préfixe, etc.
    // (pour un V autre que double/string, inclure "Expression.tpp")
    template <typename V>
    static V parcourirInfixe(const std::string& expr,
                             std::function<V(const Token&)> feuille,
                             std::function<V(char, const V&, const V&)> combiner);

    static double evaluer(const std::string& expr);

    // Infixe -> préfixe (notation polonaise) : "op a b"
    static std::string versPrefixe(const std::string& expr);

    // Infixe -> postfixe (notation polonaise inverse) : "a b op"
    static std::string versPostfixe(const std::string& expr);

    // Parcours générique d'une expression préfixe (jetons séparés par des
    // espaces), lue de droite à gauche avec une seule pile de valeurs.
    template <typename V>
    static V parcourirPrefixe(const std::string& prefixe,
                              std::function<V(const std::string&)> feuille,
                              std::function<V(char, const V&, const V&)> combiner);

    // Préfixe -> infixe (entièrement parenthésée)
    static std::string prefixeVersInfixe(const std::string& prefixe);

    static double evaluerPrefixe(const std::string& prefixe);
};

// Instanciations fournies par libpile.so
extern template class PileTableau<Token>;
extern template class PileListe<Token>;
extern template class Analyseur<PileTableau>;
extern template class Analyseur<PileListe>;

#endif
