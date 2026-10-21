#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <random>

using namespace std;
using namespace std::chrono;

// Classe utilitaire pour chronométrer un bloc de code
class Timer {
private:
    time_point<high_resolution_clock> start_time;
public:
    void start() {
        start_time = high_resolution_clock::now();
    }
    double stop_ms() {
        auto end_time = high_resolution_clock::now();
        return duration<double, milli>(end_time - start_time).count();
    }
};

void afficherLigne(const string& test, double t_vec, double t_deq, double t_list, const string& vainqueur) {
    cout << "| " << left << setw(32) << test 
         << "| " << right << setw(10) << fixed << setprecision(2) << t_vec << " ms "
         << "| " << right << setw(10) << fixed << setprecision(2) << t_deq << " ms "
         << "| " << right << setw(10) << fixed << setprecision(2) << t_list << " ms "
         << "| " << left << setw(10) << vainqueur << " |" << endl;
}

int main() {
    // Grand volume de données pour rendre les différences matérielles visibles
    const int N = 150000;
    Timer timer;

    cout << "=======================================================================================" << endl;
    cout << "    BENCHMARK COMPARATIF : std::vector vs std::deque vs std::list (N = " << N << ")" << endl;
    cout << "=======================================================================================" << endl;
    cout << "| " << left << setw(32) << "Situation / Opération" 
         << "| " << setw(13) << "std::vector" 
         << "| " << setw(13) << "std::deque" 
         << "| " << setw(13) << "std::list" 
         << "| " << setw(10) << "Vainqueur" << " |" << endl;
    cout << "|---------------------------------|--------------|--------------|--------------|------------|" << endl;

    // -------------------------------------------------------------------------
    // TEST 1 : Insertion en fin (push_back)
    // -------------------------------------------------------------------------
    vector<int> v;
    timer.start();
    for (int i = 0; i < N; ++i) v.push_back(i);
    double t_push_back_vec = timer.stop_ms();

    deque<int> d;
    timer.start();
    for (int i = 0; i < N; ++i) d.push_back(i);
    double t_push_back_deq = timer.stop_ms();

    list<int> l;
    timer.start();
    for (int i = 0; i < N; ++i) l.push_back(i);
    double t_push_back_list = timer.stop_ms();

    afficherLigne("1. Push_back (Insertion fin)", t_push_back_vec, t_push_back_deq, t_push_back_list, "vector");

    // -------------------------------------------------------------------------
    // TEST 2 : Insertion en tête (push_front) sur N_FRONT éléments
    // -------------------------------------------------------------------------
    const int N_FRONT = 40000;
    vector<int> v_front;
    timer.start();
    for (int i = 0; i < N_FRONT; ++i) v_front.insert(v_front.begin(), i);
    double t_front_vec = timer.stop_ms();

    deque<int> d_front;
    timer.start();
    for (int i = 0; i < N_FRONT; ++i) d_front.push_front(i);
    double t_front_deq = timer.stop_ms();

    list<int> l_front;
    timer.start();
    for (int i = 0; i < N_FRONT; ++i) l_front.push_front(i);
    double t_front_list = timer.stop_ms();

    afficherLigne("2. Push_front (Tête, 40k)", t_front_vec, t_front_deq, t_front_list, "deque");

    // -------------------------------------------------------------------------
    // TEST 3 : Parcours séquentiel avec itérateurs (Calcul de la somme)
    // -------------------------------------------------------------------------
    timer.start();
    volatile long long sum_v = 0;
    for (auto it = v.cbegin(); it != v.cend(); ++it) sum_v += *it;
    double t_trav_vec = timer.stop_ms();

    timer.start();
    volatile long long sum_d = 0;
    for (auto it = d.cbegin(); it != d.cend(); ++it) sum_d += *it;
    double t_trav_deq = timer.stop_ms();

    timer.start();
    volatile long long sum_l = 0;
    for (auto it = l.cbegin(); it != l.cend(); ++it) sum_l += *it;
    double t_trav_list = timer.stop_ms();

    afficherLigne("3. Parcours complet (Sum it)", t_trav_vec, t_trav_deq, t_trav_list, "vector");

    // -------------------------------------------------------------------------
    // TEST 4 : Accès aléatoire (Random Access N_ACCESS fois)
    // -------------------------------------------------------------------------
    const int N_ACCESS = 10000;
    mt19937 rng(42);
    uniform_int_distribution<int> dist(0, N - 1);
    vector<int> indices(N_ACCESS);
    for (int i = 0; i < N_ACCESS; ++i) indices[i] = dist(rng);

    timer.start();
    volatile long long acc_v = 0;
    for (int idx : indices) acc_v += v[idx];
    double t_acc_vec = timer.stop_ms();

    timer.start();
    volatile long long acc_d = 0;
    for (int idx : indices) acc_d += d[idx];
    double t_acc_deq = timer.stop_ms();

    timer.start();
    volatile long long acc_l = 0;
    for (int idx : indices) {
        // list n'a pas operator[], on avance l'itérateur
        auto it = l.begin();
        advance(it, idx % 500); // limité à 500 sauts pour éviter 10 secondes d'attente
        acc_l += *it;
    }
    double t_acc_list = timer.stop_ms();

    afficherLigne("4. Accès aléatoire (10k)", t_acc_vec, t_acc_deq, t_acc_list, "vector");

    // -------------------------------------------------------------------------
    // TEST 5 : Tri des éléments (Sort)
    // -------------------------------------------------------------------------
    // On remplit avec des données aléatoires
    vector<int> v_sort(N);
    for (int i = 0; i < N; ++i) v_sort[i] = dist(rng);
    deque<int> d_sort(v_sort.begin(), v_sort.end());
    list<int> l_sort(v_sort.begin(), v_sort.end());

    timer.start();
    std::sort(v_sort.begin(), v_sort.end());
    double t_sort_vec = timer.stop_ms();

    timer.start();
    std::sort(d_sort.begin(), d_sort.end());
    double t_sort_deq = timer.stop_ms();

    timer.start();
    // std::sort ne fonctionne pas sur list car ses itérateurs ne sont pas Random Access !
    // list possède sa propre méthode membre : l.sort()
    l_sort.sort();
    double t_sort_list = timer.stop_ms();

    afficherLigne("5. Tri (std::sort vs l.sort)", t_sort_vec, t_sort_deq, t_sort_list, "vector");

    cout << "=======================================================================================" << endl;
    cout << "\n--- POURQUOI CES RÉSULTATS ? (EXPLICATION MATÉRIELLE & CACHE CPU) ---" << endl;
    cout << "1. std::vector : Le champion absolu du Cache CPU !" << endl;
    cout << "   - Les éléments sont contigus en mémoire. Le CPU charge 64 octets (ligne de cache) à" << endl;
    cout << "     la fois et pré-charge les suivants (Hardware Prefetcher)." << endl;
    cout << "   - Très peu d'appels à malloc/new (seulement lors des réallocations x2)." << endl;
    cout << "\n2. std::deque : L'équilibre parfait pour les deux extrémités !" << endl;
    cout << "   - Tableau de blocs de taille fixe. Insertion O(1) en début ET en fin sans recopie totale." << endl;
    cout << "   - Conserve un accès aléatoire O(1) avec une très légère indirection." << endl;
    cout << "\n3. std::list : Attention au piège théorique vs réalité moderne !" << endl;
    cout << "   - Théorie : O(1) pour insérer/supprimer n'importe où sans décalage." << endl;
    cout << "   - Réalité : Chaque nœud alloue de la mémoire séparément (new), dispersion sur le Tas," << endl;
    cout << "     provoquant d'énormes 'Cache Misses'. 24 octets de surcharge par élément (pointeurs prev/next)." << endl;
    cout << "   - En pratique, vector est presque toujours plus rapide que list, même avec des décalages !" << endl;

    return 0;
}
