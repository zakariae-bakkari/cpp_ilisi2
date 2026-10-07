// Exercice 2 : meme recherche que l'exercice 1 mais les mots sont lus dans un fichier
// on demande mot1, puis on cherche chaque mot du fichier dans mot1
// fichier10.txt : 10 mots, fichier10000.txt : 10 000 mots
// fichier10000000.txt : 10 millions de mots, fichier100000000.txt : 100 millions de mots
//
// complexite :
//   recherche(s1, s2) : O(n) avec n = taille de s1 (pos avance toujours dans s1)
//   rechercheFichier  : O(N * n) avec N = nombre de mots du fichier
//   n est petit et fixe (mot1), donc le temps est lineaire en N : O(N)
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

bool recherche(string s1, string s2)
{
    size_t pos = 0;

    for (size_t i = 0; i < s2.size(); i++)
    {
        size_t p = s1.find(s2[i], pos);

        if (p == string::npos)
            return false;

        pos = p + 1;
    }

    return true;
}

// cherche tous les mots du fichier dans mot1 et affiche le temps
void rechercheFichier(string nomFichier, string mot1)
{
    ifstream f(nomFichier);

    if (!f)
    {
        cout << "impossible d'ouvrir " << nomFichier << endl;
        return;
    }

    // debut du temps
    clock_t debut = clock();

    string mot2;
    int nbMots = 0;
    int nbTrouves = 0;

    // on lit un mot a chaque tour jusqu'a la fin du fichier
    while (f >> mot2)
    {
        nbMots++;

        if (recherche(mot1, mot2))
            nbTrouves++;
    }

    // fin du temps
    clock_t fin = clock();
    double temps = (double)(fin - debut) * 1000 / CLOCKS_PER_SEC;

    f.close();

    cout << nomFichier << " : " << nbTrouves << " mots trouves sur " << nbMots << endl;
    cout << "temps d'execution : " << temps << " ms" << endl;

    // temps moyen pour un mot, pour comparer les fichiers entre eux
    if (nbMots > 0)
        cout << "temps par mot : " << temps * 1000000 / nbMots << " ns" << endl;

    cout << endl;
}

int main()
{
    string mot1;

    cout << "mot 1 : ";
    cin >> mot1;

    rechercheFichier("fichier10.txt", mot1);
    rechercheFichier("fichier10000.txt", mot1);
    rechercheFichier("fichier10000000.txt", mot1);
    rechercheFichier("fichier100000000.txt", mot1);

    return 0;
}
