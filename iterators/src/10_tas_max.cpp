#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <random>

using namespace std;
using namespace std::chrono;

// ==============================================================================
// TAS MAX : INSERTIONS + EXTRACTION DU MAX SUR LES VALEURS DE data/data.txt
// ==============================================================================

// Tas max range dans un tableau : pour la case i, le parent est en (i-1)/2,
// les enfants en 2i+1 et 2i+2. Chaque parent est plus grand que ses enfants,
// donc le maximum est toujours en tas[0].
class TasMax {
    vector<int> tas;
    long echanges = 0;  // nombre de swaps, pour comparer les cas

    // Fait remonter la case i : tant qu'elle est plus grande que son parent,
    // on les echange. S'arrete a la racine ou quand le parent est plus grand.
    void monter(int i) {
        while (i > 0 && tas[(i - 1) / 2] < tas[i]) {
            swap(tas[i], tas[(i - 1) / 2]);
            echanges++;
            i = (i - 1) / 2;
        }
    }

    // Fait descendre la case i : on l'echange avec le plus grand de ses deux
    // enfants tant qu'il est plus grand qu'elle. S'arrete quand elle est a sa
    // place ou qu'elle n'a plus d'enfant.
    void descendre(int i) {
        int n = tas.size();
        while (true) {
            int max = i;
            int g = 2 * i + 1;
            int d = 2 * i + 2;
            if (g < n && tas[g] > tas[max]) max = g;
            if (d < n && tas[d] > tas[max]) max = d;
            if (max == i) return;
            swap(tas[i], tas[max]);
            echanges++;
            i = max;
        }
    }

public:
    // Insertion : ajoute la valeur dans la premiere case libre (a la fin),
    // puis la fait remonter. O(log n).
    void inserer(int val) {
        tas.push_back(val);
        monter(tas.size() - 1);
    }

    // Extraction : retire et renvoie la racine (le max). Le dernier element
    // prend sa place, puis on l'ajuste en le faisant descendre. O(log n).
    int extraireMax() {
        int racine = tas[0];
        tas[0] = tas.back();
        tas.pop_back();
        if (!tas.empty()) descendre(0);
        return racine;
    }

    // Renvoie le max (la racine) sans le retirer. O(1).
    int max() const { return tas[0]; }

    // Renvoie le nombre d'echanges depuis le dernier appel, puis le remet a 0.
    long prendreEchanges() {
        long n = echanges;
        echanges = 0;
        return n;
    }
};

// Duree entre deux instants, en millisecondes.
double get_ms(time_point<high_resolution_clock> start, time_point<high_resolution_clock> end) {
    return duration<double, milli>(end - start).count();
}

// Duree entre deux instants, en microsecondes.
double get_us(time_point<high_resolution_clock> start, time_point<high_resolution_clock> end) {
    return duration<double, micro>(end - start).count();
}

// Lit tous les entiers du fichier (essaie aussi ../ si lance depuis un
// sous-dossier). Renvoie un vecteur vide si le fichier est introuvable.
vector<int> lire_fichier(const string& nom) {
    vector<int> valeurs;
    ifstream f(nom);
    if (!f) f.open("../" + nom);
    int val;
    while (f >> val) valeurs.push_back(val);
    return valeurs;
}

// Insere toutes les valeurs dans un tas, puis extrait UNE fois le max (la
// racine) et reorganise le tas. Affiche une ligne : temps et echanges de
// chaque phase, le max extrait et le nouveau max apres reorganisation.
void mesurer(const string& titre, const vector<int>& valeurs) {
    TasMax tas;

    auto t1 = high_resolution_clock::now();
    for (int v : valeurs) tas.inserer(v);
    auto t2 = high_resolution_clock::now();
    double t_insertions = get_ms(t1, t2);
    long e_insertions = tas.prendreEchanges();

    t1 = high_resolution_clock::now();
    int extrait = tas.extraireMax();
    t2 = high_resolution_clock::now();
    double t_extraction = get_us(t1, t2);
    long e_extraction = tas.prendreEchanges();

    cout << "| " << left << setw(16) << titre
         << "| " << right << setw(8) << fixed << setprecision(3) << t_insertions << " ms "
         << "| " << right << setw(8) << t_extraction << " us "
         << "| " << right << setw(9) << e_insertions << " "
         << "| " << right << setw(9) << e_extraction << " "
         << "| " << right << setw(7) << extrait << " "
         << "| " << right << setw(7) << tas.max() << " |\n";
}

// Lit data/data.txt (ou le fichier passe en argument), puis mesure le tas
// sur les valeurs dans l'ordre du fichier (triees) et sur les memes melangees.
int main(int argc, char* argv[]) {
    string fichier = argc > 1 ? argv[1] : "data/data.txt";
    vector<int> valeurs = lire_fichier(fichier);
    if (valeurs.empty()) {
        cerr << "Impossible de lire " << fichier << "\n";
        return 1;
    }

    vector<int> melangees = valeurs;
    shuffle(melangees.begin(), melangees.end(), mt19937(42));

    string ligne(97, '=');
    cout << "\n" << ligne << "\n";
    cout << "   TAS MAX -- " << valeurs.size() << " valeurs lues depuis " << fichier << "\n";
    cout << ligne << "\n";
    cout << "|                 |            Temps            |       Echanges        |  Max   | Nouveau |\n";
    cout << "| " << left << setw(16) << "Ordre"
         << "| " << setw(12) << "Insertions"
         << "| " << setw(12) << "Extr. max"
         << "| " << setw(10) << "Insert."
         << "| " << setw(10) << "Extract."
         << "| " << setw(8) << "extrait"
         << "| " << setw(8) << "max" << "|\n";
    cout << "|-----------------|-------------|-------------|-----------|-----------|---------|---------|\n";

    mesurer("Fichier (trie)", valeurs);
    mesurer("Melangees", melangees);

    cout << ligne << "\n";
    cout << "Insertions   : n insertions avec remontee, O(n log n).\n";
    cout << "Extract. max : un seul extraireMax() (racine retiree + reorganisation), O(log n).\n";

    return 0;
}
