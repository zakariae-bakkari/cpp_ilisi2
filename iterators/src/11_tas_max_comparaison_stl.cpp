#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <random>

using namespace std;
using namespace std::chrono;

// ==============================================================================
// TAS MAX : COMPARAISON std::priority_queue / std::set / std::map
// ==============================================================================
// Memes mesures que le programme 10 : inserer toutes les valeurs, puis retirer
// le maximum jusqu'a ce que la structure soit vide.
//   priority_queue : un tas max dans un vector (comme notre TasMax).
//                    push(v), puis top() + pop().
//   set            : arbre rouge-noir trie, le max est le dernier element.
//                    insert(v), puis erase(prev(end())). Les doublons sont
//                    ignores (data/data.txt n'en contient pas).
//   map            : arbre rouge-noir valeur -> nombre d'occurrences.
//                    m[v]++, puis on decremente ou on efface prev(end()).

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
    volatile long garde = somme;  // empeche le compilateur de supprimer la boucle
    (void)garde;
    return {t_ins, get_ms(t1, t2)};
}

// set : insert() de chaque valeur, puis on lit et efface le dernier element
// (le plus grand) jusqu'au vide.
Temps mesurer_set(const vector<int>& valeurs) {
    set<int> s;

    auto t1 = high_resolution_clock::now();
    for (int v : valeurs) s.insert(v);
    auto t2 = high_resolution_clock::now();
    double t_ins = get_ms(t1, t2);

    long somme = 0;
    t1 = high_resolution_clock::now();
    while (!s.empty()) {
        auto max = prev(s.end());
        somme += *max;
        s.erase(max);
    }
    t2 = high_resolution_clock::now();
    volatile long garde = somme;
    (void)garde;
    return {t_ins, get_ms(t1, t2)};
}

// map : compte les occurrences de chaque valeur, puis retire le max une
// occurrence a la fois (la cle est effacee quand son compteur tombe a 0).
Temps mesurer_map(const vector<int>& valeurs) {
    map<int, int> m;

    auto t1 = high_resolution_clock::now();
    for (int v : valeurs) m[v]++;
    auto t2 = high_resolution_clock::now();
    double t_ins = get_ms(t1, t2);

    long somme = 0;
    t1 = high_resolution_clock::now();
    while (!m.empty()) {
        auto max = prev(m.end());
        somme += max->first;
        if (--max->second == 0) m.erase(max);
    }
    t2 = high_resolution_clock::now();
    volatile long garde = somme;
    (void)garde;
    return {t_ins, get_ms(t1, t2)};
}

// Affiche une ligne du tableau : une mesure (ordre + phase) pour les trois
// structures, une colonne par structure.
void afficher(const string& ligne, double pq, double st, double mp) {
    cout << "| " << left << setw(27) << ligne << fixed << setprecision(3)
         << "| " << right << setw(11) << pq << " ms "
         << "| " << right << setw(11) << st << " ms "
         << "| " << right << setw(11) << mp << " ms |\n";
}

// Lit data/data.txt (ou le fichier passe en argument), puis mesure les trois
// structures sur les valeurs dans l'ordre du fichier (triees) et melangees.
int main(int argc, char* argv[]) {
    string fichier = argc > 1 ? argv[1] : "data/data.txt";
    vector<int> valeurs = lire_fichier(fichier);
    if (valeurs.empty()) {
        cerr << "Impossible de lire " << fichier << "\n";
        return 1;
    }

    vector<int> melangees = valeurs;
    shuffle(melangees.begin(), melangees.end(), mt19937(42));

    // Passage non mesure : la premiere structure a noeuds paie la reservation
    // de la memoire par le systeme, ce qui fausserait la comparaison.
    mesurer_map(melangees);

    Temps pq_trie = mesurer_priority_queue(valeurs);
    Temps pq_mel = mesurer_priority_queue(melangees);
    Temps set_trie = mesurer_set(valeurs);
    Temps set_mel = mesurer_set(melangees);
    Temps map_trie = mesurer_map(valeurs);
    Temps map_mel = mesurer_map(melangees);

    cout << "\n===================================================================================\n";
    cout << "   TAS MAX / STL -- " << valeurs.size() << " valeurs lues depuis " << fichier << "\n";
    cout << "===================================================================================\n";
    cout << "| " << left << setw(27) << "Ordre + phase"
         << "| " << setw(15) << "priority_queue"
         << "| " << setw(15) << "set"
         << "| " << setw(15) << "map" << "|\n";
    cout << "|----------------------------|----------------|----------------|----------------|\n";

    afficher("Fichier (trie) insertions", pq_trie.insertions, set_trie.insertions, map_trie.insertions);
    afficher("Fichier (trie) extractions", pq_trie.extractions, set_trie.extractions, map_trie.extractions);
    afficher("Melangees insertions", pq_mel.insertions, set_mel.insertions, map_mel.insertions);
    afficher("Melangees extractions", pq_mel.extractions, set_mel.extractions, map_mel.extractions);

    cout << "===================================================================================\n";
    cout << "priority_queue : tas dans un vector, insertion et extraction O(log n).\n";
    cout << "set / map      : arbre rouge-noir (un noeud alloue par valeur),\n";
    cout << "                 insertion O(log n), max = prev(end()).\n";

    return 0;
}
