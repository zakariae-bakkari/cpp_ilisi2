#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <random>

using namespace std;
using namespace std::chrono;

// =======================================================================================
// TAS MAX : NOTRE TasMax COMPARE A std::priority_queue
// =======================================================================================
// std::priority_queue<int> est le tas max fourni par la STL : il range aussi
// les valeurs dans un vector, et top() renvoie toujours le maximum.
//   push(v) : equivalent de inserer(v)    (ajout a la fin + remontee)
//   pop()   : equivalent de extraireMax() (dernier a la racine + descente)
// Les deux sont mesures dans le meme programme, sur les memes valeurs :
// toutes les insertions, puis UNE extraction du max (+ reorganisation).

// Notre tas max (meme classe que le programme 10, sans le compteur d'echanges).
// Pour la case i, le parent est en (i-1)/2, les enfants en 2i+1 et 2i+2.
class TasMax {
    vector<int> tas;

    // Fait remonter la case i tant qu'elle est plus grande que son parent.
    void monter(int i) {
        while (i > 0 && tas[(i - 1) / 2] < tas[i]) {
            swap(tas[i], tas[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    // Fait descendre la case i en l'echangeant avec le plus grand de ses
    // enfants, tant que cet enfant est plus grand qu'elle.
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
            i = max;
        }
    }

public:
    // Ajoute la valeur a la fin puis la fait remonter. O(log n).
    void inserer(int val) {
        tas.push_back(val);
        monter(tas.size() - 1);
    }

    // Retire et renvoie la racine (le max) : le dernier element prend sa
    // place puis descend. O(log n).
    int extraireMax() {
        int racine = tas[0];
        tas[0] = tas.back();
        tas.pop_back();
        if (!tas.empty()) descendre(0);
        return racine;
    }

    // Renvoie le max (la racine) sans le retirer. O(1).
    int max() const { return tas[0]; }
};

struct Temps {
    double insertions;  // ms
    double extraction;  // us
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

// Notre tas : inserer() de chaque valeur, puis un seul extraireMax().
Temps mesurer_tas_max(const vector<int>& valeurs) {
    TasMax tas;

    auto t1 = high_resolution_clock::now();
    for (int v : valeurs) tas.inserer(v);
    auto t2 = high_resolution_clock::now();
    double t_ins = get_ms(t1, t2);

    t1 = high_resolution_clock::now();
    volatile int extrait = tas.extraireMax();  // volatile : le resultat est garde
    t2 = high_resolution_clock::now();
    (void)extrait;
    return {t_ins, get_us(t1, t2)};
}

// priority_queue : push() de chaque valeur, puis un seul top() + pop().
Temps mesurer_priority_queue(const vector<int>& valeurs) {
    priority_queue<int> pq;

    auto t1 = high_resolution_clock::now();
    for (int v : valeurs) pq.push(v);
    auto t2 = high_resolution_clock::now();
    double t_ins = get_ms(t1, t2);

    t1 = high_resolution_clock::now();
    volatile int extrait = pq.top();
    pq.pop();
    t2 = high_resolution_clock::now();
    (void)extrait;
    return {t_ins, get_us(t1, t2)};
}

// Affiche une ligne du tableau : une mesure (ordre + phase) pour les deux
// versions, puis la plus rapide et de combien.
void afficher(const string& ligne, double tas, double pq, const string& unite) {
    string gagnant = tas < pq ? "TasMax" : "priority_queue";
    double rapport = tas < pq ? pq / tas : tas / pq;
    cout << "| " << left << setw(30) << ligne << fixed << setprecision(3)
         << "| " << right << setw(9) << tas << " " << unite << " "
         << "| " << right << setw(11) << pq << " " << unite << " "
         << "| " << left << setw(14) << gagnant
         << " x" << setprecision(2) << rapport << " |\n";
}

// Lit data/data.txt (ou le fichier passe en argument), puis mesure les deux
// versions sur les valeurs dans l'ordre du fichier (triees) et melangees.
int main(int argc, char* argv[]) {
    string fichier = argc > 1 ? argv[1] : "data/data.txt";
    vector<int> valeurs = lire_fichier(fichier);
    if (valeurs.empty()) {
        cerr << "Impossible de lire " << fichier << "\n";
        return 1;
    }

    vector<int> melangees = valeurs;
    shuffle(melangees.begin(), melangees.end(), mt19937(42));

    Temps tas_trie = mesurer_tas_max(valeurs);
    Temps pq_trie = mesurer_priority_queue(valeurs);
    Temps tas_mel = mesurer_tas_max(melangees);
    Temps pq_mel = mesurer_priority_queue(melangees);

    cout << "\n=======================================================================================\n";
    cout << "   TasMax vs std::priority_queue -- " << valeurs.size() << " valeurs lues depuis " << fichier << "\n";
    cout << "=======================================================================================\n";
    cout << "| " << left << setw(30) << "Ordre + phase"
         << "| " << setw(13) << "TasMax"
         << "| " << setw(15) << "priority_queue"
         << "| " << setw(20) << "Plus rapide" << "|\n";
    cout << "|-------------------------------|--------------|----------------|---------------------|\n";

    afficher("Fichier (trie) insertions", tas_trie.insertions, pq_trie.insertions, "ms");
    afficher("Fichier (trie) extraction max", tas_trie.extraction, pq_trie.extraction, "us");
    afficher("Melangees insertions", tas_mel.insertions, pq_mel.insertions, "ms");
    afficher("Melangees extraction max", tas_mel.extraction, pq_mel.extraction, "us");

    cout << "=======================================================================================\n";
    cout << "Les deux sont un tas max dans un vector : insertion et extraction O(log n).\n";
    cout << "Extraction max : un seul retrait de la racine + reorganisation (en microsecondes).\n";
    cout << "x2.00 = deux fois plus rapide que l'autre version.\n";

    return 0;
}
