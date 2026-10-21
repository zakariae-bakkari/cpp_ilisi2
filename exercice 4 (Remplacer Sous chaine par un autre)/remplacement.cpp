// Exercice 3 : remplacement d'une sous chaine dans un fichier
// on demande le nom du fichier, la sous chaine a chercher (ancien) et la nouvelle (nouveau)
// chaque occurrence de ancien dans le fichier est remplacee par nouveau
// le resultat est ecrit dans un nouveau fichier : resultat.txt
//
// complexite :
//   remplacer(ligne, ancien, nouveau) : O(L * a) au pire avec L = taille de la ligne, a = taille de ancien
//   remplacementFichier : O(T * a) avec T = taille totale du fichier, a petit donc lineaire en T
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

// remplace toutes les occurrences de ancien par nouveau dans ligne
// retourne le nombre de remplacements faits
int remplacer(string &ligne, string ancien, string nouveau)
{
    if (ancien.empty())
        return 0;

    int nb = 0;
    size_t pos = 0;

    // on cherche ancien a partir de pos
    while ((pos = ligne.find(ancien, pos)) != string::npos)
    {
        ligne.replace(pos, ancien.size(), nouveau);

        // on saute le texte ajoute pour ne pas le remplacer une 2eme fois
        // ex: ancien = "a", nouveau = "aa"
        pos += nouveau.size();
        nb++;
    }

    return nb;
}

// lit le fichier ligne par ligne, remplace et ecrit dans nomSortie
void remplacementFichier(string nomFichier, string nomSortie, string ancien, string nouveau)
{
    ifstream f(nomFichier);

    if (!f)
    {
        cout << "impossible d'ouvrir " << nomFichier << endl;
        return;
    }

    ofstream s(nomSortie);

    if (!s)
    {
        cout << "impossible de creer " << nomSortie << endl;
        return;
    }

    // debut du temps
    clock_t debut = clock();

    string ligne;
    long nbLignes = 0;
    long nbRemplacements = 0;

    while (getline(f, ligne))
    {
        nbLignes++;
        nbRemplacements += remplacer(ligne, ancien, nouveau);
        s << ligne << '\n';
    }

    // fin du temps
    clock_t fin = clock();
    double temps = (double)(fin - debut) * 1000 / CLOCKS_PER_SEC;

    f.close();
    s.close();

    cout << nomFichier << " : " << nbRemplacements << " remplacements sur " << nbLignes << " lignes" << endl;
    cout << "resultat ecrit dans " << nomSortie << endl;
    cout << "temps d'execution : " << temps << " ms" << endl;
}

int main()
{
    string nomFichier, ancien, nouveau;

    cout << "fichier : ";
    cin >> nomFichier;
    cout << "sous chaine a remplacer : ";
    cin >> ancien;
    cout << "remplacer par : ";
    cin >> nouveau;

    remplacementFichier(nomFichier, "resultat.txt", ancien, nouveau);

    return 0;
}
