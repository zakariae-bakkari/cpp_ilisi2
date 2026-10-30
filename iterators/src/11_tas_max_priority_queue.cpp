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
// TAS MAX AVEC std::priority_queue : MEMES MESURES QUE LE PROGRAMME 10
// ==============================================================================
// std::priority_queue<int> est un tas max fourni par la STL : il range aussi
// les valeurs dans un vector, et top() renvoie toujours le maximum.
//   push(v) : equivalent de inserer(v)    (ajout a la fin + remontee)
//   pop()   : equivalent de extraireMax() (dernier a la racine + descente)

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

// Insere toutes les valeurs avec push(), puis retire le max avec top() + pop()
// jusqu'a vider la file. Affiche une ligne : temps de chaque phase.
void mesurer(const string& titre, const vector<int>& valeurs) {
    priority_queue<int> tas;

    auto t1 = high_resolution_clock::now();
    for (int v : valeurs) tas.push(v);
    auto t2 = high_resolution_clock::now();
    double t_insertions = get_ms(t1, t2);

    long somme = 0;
    t1 = high_resolution_clock::now();
    while (!tas.empty()) {
        somme += tas.top();
        tas.pop();
    }
    t2 = high_resolution_clock::now();
    double t_extraction = get_ms(t1, t2);

    cout << "| " << left << setw(20) << titre
         << "| " << right << setw(10) << fixed << setprecision(3) << t_insertions << " ms "
         << "| " << right << setw(10) << t_extraction << " ms |\n";
    volatile long garde = somme;  // empeche le compilateur de supprimer la boucle
    (void)garde;
}

// Lit data/data.txt (ou le fichier passe en argument), puis mesure la file
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

    cout << "\n=====================================================\n";
    cout << "   std::priority_queue -- " << valeurs.size() << " valeurs lues depuis " << fichier << "\n";
    cout << "=====================================================\n";
    cout << "| " << left << setw(20) << "Ordre des valeurs"
         << "| " << setw(14) << "push()"
         << "| " << setw(14) << "top() + pop()" << "|\n";
    cout << "|---------------------|---------------|---------------|\n";

    mesurer("Fichier (trie)", valeurs);
    mesurer("Melangees", melangees);

    cout << "=====================================================\n";
    cout << "push()        : n insertions, O(n log n).\n";
    cout << "top() + pop() : retirer le max jusqu'a la file vide, O(n log n).\n";

    return 0;
}
