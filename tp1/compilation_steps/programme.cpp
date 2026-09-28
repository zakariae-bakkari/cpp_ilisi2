/*
 * programme.cpp
 * -------------
 * Petit programme de démonstration des étapes de compilation :
 *   1. prétraitement  (g++ -E)  -> programme.ii
 *   2. compilation    (g++ -S)  -> programme.s
 *   3. assemblage     (g++ -c)  -> programme.o
 *   4. édition de liens         -> programme (lié à libpile.so)
 *
 * Il contient volontairement des #include, des macros, de la compilation
 * conditionnelle, des commentaires et des espaces / lignes vides, pour voir
 * ce que le préprocesseur en fait.
 */

#include <iostream>        // include système : recopié en entier par le préprocesseur
#include <string>
#include "PileTableau.h"   // include du projet : pile fournie par libpile.so


// ---- Macros : remplacées textuellement pendant le prétraitement ----
#define TAILLE_MAX   5
#define CARRE(x)     ((x) * (x))
#define MESSAGE      "Demonstration des etapes de compilation"

// Compilation conditionnelle : DEBUG n'est pas défini par défaut,
// le bloc #ifdef disparaît donc du fichier prétraité.
// (essayer : make clean && make DEBUG=1)
#ifdef DEBUG
    #define TRACE(msg)   std::cout << "[debug] " << msg << std::endl
#else
    #define TRACE(msg)
#endif


using namespace std;



int main()
{
    cout << MESSAGE << endl;       /* commentaire en fin de ligne */

    PileTableau<int>   pile;       // espaces multiples : sans effet
    //constante

    // empile les carrés de 1 à TAILLE_MAX
    for (int i = 1; i <= TAILLE_MAX; i++)
    {
        pile.empiler(CARRE(i));
        TRACE("empiler " << CARRE(i));
    }

    cout << "Pile : ";
    pile.afficher();
    cout << endl;

    /* dépile tout :
       les éléments sortent dans l'ordre inverse (LIFO) */
    cout << "Depilement :";
    while (!pile.estVide())
        cout << " " << pile.depiler();
    cout << endl;

    cout << "Fichier : " << __FILE__ << ", ligne " << __LINE__ << endl;   // macros prédéfinies
    return 0;
}
