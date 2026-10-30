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
// TAS MAX : INSERTIONS + EXTRACTIONS SUR LES VALEURS DE data/data.txt
// ==============================================================================

class TasMax {
    vector<int> tas;
    long echanges = 0;

    void monter(int i) {
        while (i > 0 && tas[(i - 1) / 2] < tas[i]) {
            swap(tas[i], tas[(i - 1) / 2]);
            echanges++;
            i = (i - 1) / 2;
        }
    }

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
    void inserer(int val) {
        tas.push_back(val);
        monter(tas.size() - 1);
    }

    int extraireMax() {
        int racine = tas[0];
        tas[0] = tas.back();
        tas.pop_back();
        if (!tas.empty()) descendre(0);
        return racine;
    }

    bool vide() const { return tas.empty(); }

    long prendreEchanges() {
        long n = echanges;
        echanges = 0;
        return n;
    }
};

double get_ms(time_point<high_resolution_clock> start, time_point<high_resolution_clock> end) {
    return duration<double, milli>(end - start).count();
}

vector<int> lire_fichier(const string& nom) {
    vector<int> valeurs;
    ifstream f(nom);
    if (!f) f.open("../" + nom);
    int val;
    while (f >> val) valeurs.push_back(val);
    return valeurs;
}

void mesurer(const string& titre, const vector<int>& valeurs) {
    TasMax tas;

    auto t1 = high_resolution_clock::now();
    for (int v : valeurs) tas.inserer(v);
    auto t2 = high_resolution_clock::now();
    double t_insertions = get_ms(t1, t2);
    long e_insertions = tas.prendreEchanges();

    t1 = high_resolution_clock::now();
    while (!tas.vide()) tas.extraireMax();
    t2 = high_resolution_clock::now();
    double t_extraction = get_ms(t1, t2);
    long e_extraction = tas.prendreEchanges();

    cout << "| " << left << setw(20) << titre
         << "| " << right << setw(10) << fixed << setprecision(3) << t_insertions << " ms "
         << "| " << right << setw(10) << t_extraction << " ms "
         << "| " << right << setw(9) << e_insertions << " "
         << "| " << right << setw(9) << e_extraction << " |\n";
}

int main(int argc, char* argv[]) {
    string fichier = argc > 1 ? argv[1] : "data/data.txt";
    vector<int> valeurs = lire_fichier(fichier);
    if (valeurs.empty()) {
        cerr << "Impossible de lire " << fichier << "\n";
        return 1;
    }

    vector<int> melangees = valeurs;
    shuffle(melangees.begin(), melangees.end(), mt19937(42));

    cout << "\n=============================================================================\n";
    cout << "   TAS MAX -- " << valeurs.size() << " valeurs lues depuis " << fichier << "\n";
    cout << "=============================================================================\n";
    cout << "|                     |         Temps                 |       Echanges        |\n";
    cout << "| " << left << setw(20) << "Ordre des valeurs"
         << "| " << setw(14) << "Insertions"
         << "| " << setw(14) << "Extractions"
         << "| " << setw(10) << "Insert."
         << "| " << setw(10) << "Extract." << "|\n";
    cout << "|---------------------|---------------|---------------|-----------|-----------|\n";

    mesurer("Fichier (trie)", valeurs);
    mesurer("Melangees", melangees);

    cout << "=============================================================================\n";
    cout << "Insertions  : n insertions avec remontee, O(n log n).\n";
    cout << "Extractions : extraireMax() jusqu'au tas vide (ajustement), O(n log n).\n";

    return 0;
}
