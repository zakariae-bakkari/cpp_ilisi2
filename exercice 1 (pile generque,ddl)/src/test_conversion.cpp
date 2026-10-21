// Exercice 3 : conversion infixe <-> préfixe
#include <cmath>
#include <iostream>
#include <string>
#include "Expression.h"
#include "PileListe.h"
#include "PileTableau.h"
using namespace std;

typedef Analyseur<PileTableau> A;

int main() {
    cout << "=== Infixe -> Prefixe (et postfixe) ===" << endl;
    const string infixes[] = {
        "a + b",
        "a + b * c",
        "(a + b) * c",
        "a - b - c",
        "a ^ b ^ c",
        "{ [ (a + b) * c ] - d } / e",
        "(x - y) * (x + y) ^ 2",
    };
    for (const string& e : infixes) {
        cout << "  infixe   : " << e << endl;
        cout << "  prefixe  : " << A::versPrefixe(e) << endl;
        cout << "  postfixe : " << A::versPostfixe(e) << endl << endl;
    }

    cout << "=== Prefixe -> Infixe ===" << endl;
    const string prefixes[] = {
        "+ a b",
        "* + a b c",
        "- - a b c",
        "- a - b c",
        "/ - * + a b c d e",
        "+ a",          // opérande manquant
        "+ a b c",      // opérateur manquant
        "+ a $",        // jeton invalide
    };
    for (const string& p : prefixes) {
        cout << "  " << p << "  ->  ";
        try {
            cout << A::prefixeVersInfixe(p) << endl;
        } catch (const exception& ex) {
            cout << "erreur : " << ex.what() << endl;
        }
    }

    cout << "\n=== Verification croisee : evaluer(infixe) == evaluerPrefixe(prefixe) ===" << endl;
    const string numeriques[] = {
        "3 + 4 * 2",
        "(3 + 4) * 2",
        "10 - 4 - 3",
        "2 ^ 3 ^ 2",
        "{ [ (1 + 2) * 3 ] - 4 } / 5",
        "(8 - 2) * (8 + 2) ^ 2",
    };
    int ok = 0, total = 0;
    for (const string& e : numeriques) {
        string pre = Analyseur<PileListe>::versPrefixe(e);
        double v1 = Analyseur<PileListe>::evaluer(e);
        double v2 = Analyseur<PileTableau>::evaluerPrefixe(pre);
        string retour = A::prefixeVersInfixe(pre);
        double v3 = A::evaluer(retour);   // aller-retour infixe -> préfixe -> infixe
        bool egal = fabs(v1 - v2) < 1e-9 && fabs(v1 - v3) < 1e-9;
        total++;
        if (egal) ok++;
        cout << "  " << e << "\n     prefixe = " << pre << "\n     retour  = " << retour
             << "\n     valeurs = " << v1 << " / " << v2 << " / " << v3
             << (egal ? "   [OK]" : "   [ECHEC]") << endl;
    }
    cout << "\n" << ok << "/" << total << " tests reussis" << endl;
    return 0;
}
