// Exercice 4 : on donne mot1, puis on cherche dans le fichier
// la plus longue sous chaine de mot1 (un mot du fichier dont les lettres sont dans mot1, dans le meme ordre)
// ex: mot1 = "computer", le fichier contient "cote", "cmp", "comput"... -> le plus long est "comput"
//
// complexite :
//   recherche(s1, s2) : O(n) avec n = taille de s1 (pos avance toujours dans s1)
//   plusLongueSousChaine : O(N * n) avec N = nombre de mots du fichier
//   n est petit et fixe (mot1), donc le temps est lineaire en N : O(N)
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

// retourne true si les lettres de s2 sont dans s1 dans le meme ordre
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

// cherche dans le fichier le mot le plus long qui se trouve dans mot1
void plusLongueSousChaine(string nomFichier, string mot1)
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
    string meilleur = "";
    long nbMots = 0;
    long nbTrouves = 0;

    while (f >> mot2)
    {
        nbMots++;

        // un mot plus long que mot1 ne peut pas etre dedans
        if (mot2.size() > mot1.size())
            continue;

        if (recherche(mot1, mot2))
        {
            nbTrouves++;

            if (mot2.size() > meilleur.size())
                meilleur = mot2;
        }
    }

    // fin du temps
    clock_t fin = clock();
    double temps = (double)(fin - debut) * 1000 / CLOCKS_PER_SEC;

    f.close();

    cout << nomFichier << " : " << nbTrouves << " mots trouves dans " << mot1
         << " sur " << nbMots << endl;

    if (meilleur.empty())
        cout << "aucun mot du fichier ne se trouve dans " << mot1 << endl;
    else
        cout << "plus longue sous chaine : " << meilleur << " (" << meilleur.size() << " lettres)" << endl;

    cout << "temps d'execution : " << temps << " ms" << endl;
    cout << endl;
}

int main()
{
    string mot1;

    cout << "Entrer le mot a rechercher : ";
    cin >> mot1;

    plusLongueSousChaine("fichier10.txt", mot1);
    plusLongueSousChaine("fichier10000.txt", mot1);
    plusLongueSousChaine("fichier10000000.txt", mot1);
    plusLongueSousChaine("fichier100000000.txt", mot1);

    return 0;
}
