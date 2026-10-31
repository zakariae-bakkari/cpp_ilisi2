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
    double insertions;      // les n valeurs du fichier (ms)
    double extraction;      // un seul retrait du max (us)
    double insertion_fin;   // valeur plus petite que toutes : reste en bas (us)
    double insertion_haut;  // valeur plus grande que toutes : monte a la racine (us)
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

// Notre tas : inserer() de chaque valeur, un seul extraireMax(), puis une
// insertion qui reste a la fin et une qui remonte jusqu'a la racine.
Temps mesurer_tas_max(const vector<int>& valeurs, int plus_petit, int plus_grand) {
    TasMax tas;
    Temps r;

    auto t1 = high_resolution_clock::now();
    for (int v : valeurs) tas.inserer(v);
    auto t2 = high_resolution_clock::now();
    r.insertions = get_ms(t1, t2);

    t1 = high_resolution_clock::now();
    volatile int extrait = tas.extraireMax();  // volatile : le resultat est garde
    t2 = high_resolution_clock::now();
    (void)extrait;
    r.extraction = get_us(t1, t2);

    t1 = high_resolution_clock::now();
    tas.inserer(plus_petit - 1);
    t2 = high_resolution_clock::now();
    r.insertion_fin = get_us(t1, t2);

    t1 = high_resolution_clock::now();
    tas.inserer(plus_grand + 1);
    t2 = high_resolution_clock::now();
    r.insertion_haut = get_us(t1, t2);
    return r;
}

// priority_queue : push() de chaque valeur, un seul top() + pop(), puis un
// push() qui reste a la fin et un push() qui remonte jusqu'a la racine.
Temps mesurer_priority_queue(const vector<int>& valeurs, int plus_petit, int plus_grand) {
    priority_queue<int> pq;
    Temps r;

    auto t1 = high_resolution_clock::now();
    for (int v : valeurs) pq.push(v);
    auto t2 = high_resolution_clock::now();
    r.insertions = get_ms(t1, t2);

    t1 = high_resolution_clock::now();
    volatile int extrait = pq.top();
    pq.pop();
    t2 = high_resolution_clock::now();
    (void)extrait;
    r.extraction = get_us(t1, t2);

    t1 = high_resolution_clock::now();
    pq.push(plus_petit - 1);
    t2 = high_resolution_clock::now();
    r.insertion_fin = get_us(t1, t2);

    t1 = high_resolution_clock::now();
    pq.push(plus_grand + 1);
    t2 = high_resolution_clock::now();
    r.insertion_haut = get_us(t1, t2);
    return r;
}

// Affiche une ligne du tableau : une mesure (ordre + phase) pour les deux
// versions, puis la plus rapide et de combien.
void afficher(const string& ligne, double tas, double pq, const string& unite) {
    string gagnant = tas < pq ? "TasMax" : "priority_queue";
    double rapport = tas < pq ? pq / tas : tas / pq;
    cout << "| " << left << setw(39) << ligne << fixed << setprecision(3)
         << "| " << right << setw(9) << tas << " " << unite << " "
         << "| " << right << setw(11) << pq << " " << unite << " "
         << "| " << left << setw(14) << gagnant
         << " x" << setprecision(2) << rapport << " |\n";
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

    int plus_petit = *min_element(valeurs.begin(), valeurs.end());
    int plus_grand = *max_element(valeurs.begin(), valeurs.end());
    Temps tas_trie = mesurer_tas_max(valeurs, plus_petit, plus_grand);
    Temps pq_trie = mesurer_priority_queue(valeurs, plus_petit, plus_grand);
    Temps tas_mel = mesurer_tas_max(melangees, plus_petit, plus_grand);
    Temps pq_mel = mesurer_priority_queue(melangees, plus_petit, plus_grand);

    string ligne(96, '=');
    cout << "\n" << ligne << "\n";
    cout << "   TasMax vs std::priority_queue -- " << valeurs.size() << " valeurs lues depuis " << fichier << "\n";
    cout << ligne << "\n";
    cout << "| " << left << setw(39) << "Ordre + mesure"
         << "| " << setw(13) << "TasMax"
         << "| " << setw(15) << "priority_queue"
         << "| " << setw(20) << "Plus rapide" << "|\n";
    cout << "|----------------------------------------|--------------|----------------|---------------------|\n";

    afficher("Trie : insertion des n valeurs", tas_trie.insertions, pq_trie.insertions, "ms");
    afficher("Trie : extraction du max", tas_trie.extraction, pq_trie.extraction, "us");
    afficher("Trie : insertion qui reste a la fin", tas_trie.insertion_fin, pq_trie.insertion_fin, "us");
    afficher("Trie : insertion jusqu'a la racine", tas_trie.insertion_haut, pq_trie.insertion_haut, "us");
    afficher("Melange : insertion des n valeurs", tas_mel.insertions, pq_mel.insertions, "ms");
    afficher("Melange : extraction du max", tas_mel.extraction, pq_mel.extraction, "us");
    afficher("Melange : insertion qui reste a la fin", tas_mel.insertion_fin, pq_mel.insertion_fin, "us");
    afficher("Melange : insertion jusqu'a la racine", tas_mel.insertion_haut, pq_mel.insertion_haut, "us");

    cout << ligne << "\n";
    cout << "Les deux sont un tas max dans un vector : insertion et extraction O(log n).\n";
    cout << "Reste a la fin : valeur plus petite que toutes (0 echange) ;\n";
    cout << "jusqu'a la racine : valeur plus grande que toutes (log2(n) echanges).\n";
    cout << "x2.00 = deux fois plus rapide que l'autre version.\n";
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
