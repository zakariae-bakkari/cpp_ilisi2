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

// ==============================================================================
// TAS MAX : NOTRE TasMax COMPARE A std::priority_queue
// ==============================================================================
// std::priority_queue<int> est le tas max fourni par la STL : il range aussi
// les valeurs dans un vector, et top() renvoie toujours le maximum.
//   push(v) : equivalent de inserer(v)    (ajout a la fin + remontee)
//   pop()   : equivalent de extraireMax() (dernier a la racine + descente)
// Les deux sont mesures dans le meme programme, sur les memes valeurs.

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

    // Vrai quand le tas ne contient plus aucune valeur.
    bool vide() const { return tas.empty(); }
};

struct Temps {
    double insertions;
    double extractions;
};

// Duree entre deux instants, en millisecondes.
double get_ms(time_point<high_resolution_clock> start, time_point<high_resolution_clock> end) {
    return duration<double, milli>(end - start).count();
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

// Notre tas : inserer() de chaque valeur, puis extraireMax() jusqu'au vide.
Temps mesurer_tas_max(const vector<int>& valeurs) {
    TasMax tas;

    auto t1 = high_resolution_clock::now();
    for (int v : valeurs) tas.inserer(v);
    auto t2 = high_resolution_clock::now();
    double t_ins = get_ms(t1, t2);

    long somme = 0;
    t1 = high_resolution_clock::now();
    while (!tas.vide()) somme += tas.extraireMax();
    t2 = high_resolution_clock::now();
    volatile long garde = somme;  // empeche le compilateur de supprimer la boucle
    (void)garde;
    return {t_ins, get_ms(t1, t2)};
}

// priority_queue : push() de chaque valeur, puis top() + pop() jusqu'au vide.
Temps mesurer_priority_queue(const vector<int>& valeurs) {
    priority_queue<int> pq;

    auto t1 = high_resolution_clock::now();
    for (int v : valeurs) pq.push(v);
    auto t2 = high_resolution_clock::now();
    double t_ins = get_ms(t1, t2);

    long somme = 0;
    t1 = high_resolution_clock::now();
    while (!pq.empty()) {
        somme += pq.top();
        pq.pop();
    }
    t2 = high_resolution_clock::now();
    volatile long garde = somme;
    (void)garde;
    return {t_ins, get_ms(t1, t2)};
}

// Affiche une ligne du tableau : une mesure (ordre + phase) pour les deux
// versions, puis la plus rapide et de combien.
void afficher(const string& ligne, double tas, double pq) {
    string gagnant = tas < pq ? "TasMax" : "priority_queue";
    double rapport = tas < pq ? pq / tas : tas / pq;
    cout << "| " << left << setw(27) << ligne << fixed << setprecision(3)
         << "| " << right << setw(9) << tas << " ms "
         << "| " << right << setw(11) << pq << " ms "
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

    cout << "\n======================================================================================\n";
    cout << "   TasMax vs std::priority_queue -- " << valeurs.size() << " valeurs lues depuis " << fichier << "\n";
    cout << "======================================================================================\n";
    cout << "| " << left << setw(27) << "Ordre + phase"
         << "| " << setw(13) << "TasMax"
         << "| " << setw(15) << "priority_queue"
         << "| " << setw(20) << "Plus rapide" << "|\n";
    cout << "|----------------------------|--------------|----------------|---------------------|\n";

    afficher("Fichier (trie) insertions", tas_trie.insertions, pq_trie.insertions);
    afficher("Fichier (trie) extractions", tas_trie.extractions, pq_trie.extractions);
    afficher("Melangees insertions", tas_mel.insertions, pq_mel.insertions);
    afficher("Melangees extractions", tas_mel.extractions, pq_mel.extractions);
    afficher("Total (trie)", tas_trie.insertions + tas_trie.extractions,
             pq_trie.insertions + pq_trie.extractions);
    afficher("Total (melangees)", tas_mel.insertions + tas_mel.extractions,
             pq_mel.insertions + pq_mel.extractions);

    cout << "======================================================================================\n";
    cout << "Les deux sont un tas max dans un vector : insertion et extraction O(log n).\n";
    cout << "x2.00 = deux fois plus rapide que l'autre version.\n";

    return 0;
}
