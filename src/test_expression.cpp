// Exercice 2 : vérification d'une expression mathématique avec la pile générique
#include <iostream>
#include <string>
#include "Expression.h"
#include "PileListe.h"
#include "PileTableau.h"
using namespace std;

// affiche l'expression et un curseur '^' sous la position de l'erreur
void afficherResultat(const string& expr, const Resultat& r) {
    cout << "  \"" << expr << "\"" << endl;
    if (r.valide) {
        cout << "   -> VALIDE" << endl;
    } else {
        cout << "   " << string(r.position, ' ') << "^" << endl;
        cout << "   -> INVALIDE (pos " << r.position << ") : " << r.message << endl;
    }
}

int main() {
    const string expressions[] = {
        // expressions valides
        "3 + 4 * 2",
        "(a + b) * c",
        "{ [ (1 + 2) * 3 ] - 4 } / 5",
        "[(x - y) * (x + y)] ^ 2",
        "((2))",
        // délimiteurs mal équilibrés ou mal appariés
        "(3 + 4",
        "3 + 4)",
        "(3 + 4]",
        "{ [ ( 1 + 2 ] ) }",
        // ordre des délimiteurs non respecté
        "( [ 1 + 2 ] )",
        "[ { a } ]",
        // syntaxe opérandes / opérateurs
        "3 + * 4",
        "3 4 + 5",
        "(3 + )",
        "()",
        "2 (3 + 4)",
        "* 3",
        "3 +",
        "3 # 4",
        "",
    };

    cout << "=== Verification avec PileTableau ===" << endl;
    for (const string& e : expressions)
        afficherResultat(e, Analyseur<PileTableau>::verifier(e));

    // les deux implémentations doivent donner exactement les mêmes verdicts
    int differences = 0;
    for (const string& e : expressions) {
        Resultat a = Analyseur<PileTableau>::verifier(e);
        Resultat b = Analyseur<PileListe>::verifier(e);
        if (a.valide != b.valide || a.position != b.position || a.message != b.message)
            differences++;
    }
    cout << "\nComparaison PileTableau / PileListe : " << differences << " difference(s)" << endl;

    cout << "\n=== Evaluation (respect de la priorite des operateurs) ===" << endl;
    const string calculs[] = {
        "3 + 4 * 2",
        "(3 + 4) * 2",
        "{ [ (1 + 2) * 3 ] - 4 } / 5",
        "10 - 4 - 3",
        "2 ^ 3 ^ 2",
        "100 / 10 / 5",
        "2.5 * 4",
        "1 / (2 - 2)",
        "x + 1",
    };
    for (const string& e : calculs) {
        cout << "  " << e << " = ";
        try {
            cout << Analyseur<PileListe>::evaluer(e) << endl;
        } catch (const exception& ex) {
            cout << "erreur : " << ex.what() << endl;
        }
    }
    return 0;
}
