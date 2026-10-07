// Exercice 4 : on donne deux mots mot1 et mot2
// 1) on cherche la plus longue sous chaine commune entre mot1 et mot2
//    ex: "programmation" et "grammaire" -> "gramma"
// 2) on cherche dans le fichier le mot le plus long qui contient cette sous chaine
//
// complexite :
//   sousChaineCommune(mot1, mot2) : O(n * m) avec n, m = tailles des deux mots
//   plusLongMot : O(N * k) avec N = nombre de mots du fichier, k = taille d'un mot
//   n, m et k sont petits donc le temps est lineaire en N : O(N)
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

// plus longue sous chaine commune (lettres qui se suivent) par programmation dynamique
// t[i][j] = longueur de la sous chaine commune qui finit a mot1[i-1] et mot2[j-1]
string sousChaineCommune(string mot1, string mot2)
{
    size_t n = mot1.size();
    size_t m = mot2.size();
    vector<vector<int>> t(n + 1, vector<int>(m + 1, 0));

    int maxLong = 0;
    size_t fin = 0; // position de fin de la meilleure sous chaine dans mot1

    for (size_t i = 1; i <= n; i++)
    {
        for (size_t j = 1; j <= m; j++)
        {
            // meme lettre : on prolonge la sous chaine d'avant
            if (mot1[i - 1] == mot2[j - 1])
            {
                t[i][j] = t[i - 1][j - 1] + 1;

                if (t[i][j] > maxLong)
                {
                    maxLong = t[i][j];
                    fin = i;
                }
            }
        }
    }

    return mot1.substr(fin - maxLong, maxLong);
}

// cherche le mot le plus long du fichier qui contient sousChaine
void plusLongMot(string nomFichier, string sousChaine)
{
    ifstream f(nomFichier);

    if (!f)
    {
        cout << "impossible d'ouvrir " << nomFichier << endl;
        return;
    }

    // debut du temps
    clock_t debut = clock();

    string mot;
    string meilleur = "";
    long nbMots = 0;
    long nbContient = 0;

    while (f >> mot)
    {
        nbMots++;

        if (mot.find(sousChaine) != string::npos)
        {
            nbContient++;

            if (mot.size() > meilleur.size())
                meilleur = mot;
        }
    }

    // fin du temps
    clock_t fin = clock();
    double temps = (double)(fin - debut) * 1000 / CLOCKS_PER_SEC;

    f.close();

    cout << nomFichier << " : " << nbContient << " mots contiennent \"" << sousChaine
         << "\" sur " << nbMots << endl;

    if (meilleur.empty())
        cout << "aucun mot ne contient \"" << sousChaine << "\"" << endl;
    else
        cout << "mot le plus long : " << meilleur << " (" << meilleur.size() << " lettres)" << endl;

    cout << "temps d'execution : " << temps << " ms" << endl;
}

int main()
{
    string nomFichier, mot1, mot2;

    cout << "fichier : ";
    cin >> nomFichier;
    cout << "mot 1 : ";
    cin >> mot1;
    cout << "mot 2 : ";
    cin >> mot2;

    string sc = sousChaineCommune(mot1, mot2);

    if (sc.empty())
    {
        cout << "pas de sous chaine commune entre " << mot1 << " et " << mot2 << endl;
        return 0;
    }

    cout << "sous chaine commune : " << sc << endl;

    plusLongMot(nomFichier, sc);

    return 0;
}
