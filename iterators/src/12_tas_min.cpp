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
// TAS MIN : INSERTIONS, EXTRACTION DU MIN, INSERTION A LA FIN / JUSQU'A LA RACINE
// ==============================================================================

// Tas min range dans un tableau : pour la case i, le parent est en (i-1)/2,
// les enfants en 2i+1 et 2i+2. Chaque parent est plus petit que ses enfants,
// donc le minimum est toujours en tas[0].
class TasMin {
    vector<int> tas;
    long echanges = 0;  // nombre de swaps, pour comparer les cas

    // Fait remonter la case i : tant qu'elle est plus petite que son parent,
    // on les echange. S'arrete a la racine ou quand le parent est plus petit.
    void monter(int i) {
        while (i > 0 && tas[(i - 1) / 2] > tas[i]) {
            swap(tas[i], tas[(i - 1) / 2]);
            echanges++;
            i = (i - 1) / 2;
        }
    }

    // Fait descendre la case i : on l'echange avec le plus petit de ses deux
    // enfants tant qu'il est plus petit qu'elle. S'arrete quand elle est a sa
    // place ou qu'elle n'a plus d'enfant.
    void descendre(int i) {
        int n = tas.size();
        while (true) {
            int min = i;
            int g = 2 * i + 1;
            int d = 2 * i + 2;
            if (g < n && tas[g] < tas[min]) min = g;
            if (d < n && tas[d] < tas[min]) min = d;
            if (min == i) return;
            swap(tas[i], tas[min]);
            echanges++;
            i = min;
        }
    }

public:
    // Insertion : ajoute la valeur dans la premiere case libre (a la fin),
    // puis la fait remonter. O(log n).
    void inserer(int val) {
        tas.push_back(val);
        monter(tas.size() - 1);
    }

    // Extraction : retire et renvoie la racine (le min). Le dernier element
    // prend sa place, puis on l'ajuste en le faisant descendre. O(log n).
    int extraireMin() {
        int racine = tas[0];
        tas[0] = tas.back();
        tas.pop_back();
        if (!tas.empty()) descendre(0);
        return racine;
    }

    // Renvoie le min (la racine) sans le retirer. O(1).
    int min() const { return tas[0]; }

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

// Une mesure : son temps (ms ou us) et le nombre d'echanges qu'elle a faits.
struct Mesure {
    double temps;
    long echanges;
};

// Resultats des quatre mesures faites sur un tas.
struct Resultats {
    Mesure insertions;     // les n valeurs du fichier (ms)
    Mesure extraction;     // un seul extraireMin() (us)
    Mesure insertion_fin;  // une valeur plus grande que toutes : reste en bas (us)
    Mesure insertion_haut; // une valeur plus petite que toutes : monte a la racine (us)
    int extrait, nouveau_min;
};

// Insere toutes les valeurs, extrait UNE fois le min (racine retiree +
// reorganisation), puis insere une valeur qui reste a la fin (aucun echange)
// et une valeur qui doit remonter jusqu'a la racine (log n echanges).
Resultats mesurer(const vector<int>& valeurs) {
    TasMin tas;
    Resultats r;
    int plus_petit = *min_element(valeurs.begin(), valeurs.end());
    int plus_grand = *max_element(valeurs.begin(), valeurs.end());

    auto t1 = high_resolution_clock::now();
    for (int v : valeurs) tas.inserer(v);
    auto t2 = high_resolution_clock::now();
    r.insertions = {get_ms(t1, t2), tas.prendreEchanges()};

    t1 = high_resolution_clock::now();
    r.extrait = tas.extraireMin();
    t2 = high_resolution_clock::now();
    r.extraction = {get_us(t1, t2), tas.prendreEchanges()};
    r.nouveau_min = tas.min();

    t1 = high_resolution_clock::now();
    tas.inserer(plus_grand + 1);
    t2 = high_resolution_clock::now();
    r.insertion_fin = {get_us(t1, t2), tas.prendreEchanges()};

    t1 = high_resolution_clock::now();
    tas.inserer(plus_petit - 1);
    t2 = high_resolution_clock::now();
    r.insertion_haut = {get_us(t1, t2), tas.prendreEchanges()};
    return r;
}

// Affiche une ligne du tableau : une mesure, pour le fichier trie et melange.
void afficher(const string& ligne, Mesure trie, Mesure mel, const string& unite) {
    cout << "| " << left << setw(31) << ligne << fixed << setprecision(3)
         << "| " << right << setw(9) << trie.temps << " " << unite << " "
         << "| " << right << setw(9) << trie.echanges << " "
         << "| " << right << setw(9) << mel.temps << " " << unite << " "
         << "| " << right << setw(9) << mel.echanges << " |\n";
}

// Lit le fichier, puis fait les mesures sur les valeurs dans l'ordre du
// fichier (triees) et sur les memes melangees. Renvoie false si illisible.
bool tester(const string& fichier) {
    vector<int> valeurs = lire_fichier(fichier);
    if (valeurs.empty()) {
        cerr << "\nImpossible de lire " << fichier << " (fichier absent ? voir make data)\n";
        return false;
    }

    vector<int> melangees = valeurs;
    shuffle(melangees.begin(), melangees.end(), mt19937(42));

    Resultats trie = mesurer(valeurs);
    Resultats mel = mesurer(melangees);

    string ligne(87, '=');
    cout << "\n" << ligne << "\n";
    cout << "   TAS MIN -- " << valeurs.size() << " valeurs lues depuis " << fichier << "\n";
    cout << ligne << "\n";
    cout << "|                                |     Fichier (trie)        |       Melangees           |\n";
    cout << "| " << left << setw(31) << "Mesure"
         << "| " << setw(13) << "Temps" << "| " << setw(10) << "Echanges"
         << "| " << setw(13) << "Temps" << "| " << setw(10) << "Echanges" << "|\n";
    cout << "|--------------------------------|--------------|-----------|--------------|-----------|\n";

    afficher("Insertion des n valeurs", trie.insertions, mel.insertions, "ms");
    afficher("Extraction du min", trie.extraction, mel.extraction, "us");
    afficher("Insertion qui reste a la fin", trie.insertion_fin, mel.insertion_fin, "us");
    afficher("Insertion jusqu'a la racine", trie.insertion_haut, mel.insertion_haut, "us");

    cout << ligne << "\n";
    cout << "Min extrait : " << trie.extrait << ", nouveau min apres reorganisation : "
         << trie.nouveau_min << "\n";
    cout << "Reste a la fin : valeur plus grande que toutes, son parent est plus petit (0 echange).\n";
    cout << "Jusqu'a la racine : valeur plus petite que toutes, remonte de log2(n) niveaux.\n";
    return true;
}

// Sans argument : teste data/data.txt (200 000 valeurs), data/data_1M.txt
// (1 000 000) et data/data_10M.txt (10 000 000, cree par make data).
// Avec un argument : teste seulement ce fichier.
int main(int argc, char* argv[]) {
    if (argc > 1) return tester(argv[1]) ? 0 : 1;
    bool ok = tester("data/data.txt");
    ok = tester("data/data_1M.txt") && ok;
    ok = tester("data/data_10M.txt") && ok;
    return ok ? 0 : 1;
}
