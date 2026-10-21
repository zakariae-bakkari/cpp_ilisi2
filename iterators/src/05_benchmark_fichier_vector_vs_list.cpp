#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// Mesure la durée en millisecondes avec précision
double get_ms(time_point<high_resolution_clock> start, time_point<high_resolution_clock> end) {
    return duration<double, milli>(end - start).count();
}

string resolve_input_path(const string& filename) {
    ifstream f1(filename);
    if (f1.good()) return filename;
    string f2 = "data/" + filename;
    ifstream f2_s(f2);
    if (f2_s.good()) return f2;
    string f3 = "../data/" + filename;
    ifstream f3_s(f3);
    if (f3_s.good()) return f3;
    return filename;
}

string resolve_output_path(const string& filename) {
    ifstream f2("data/data.txt");
    if (f2.good()) return "data/" + filename;
    ifstream f3("../data/data.txt");
    if (f3.good()) return "../data/" + filename;
    return filename;
}

void print_row(const string& operation, double t_vec, double t_lst) {
    string vainqueur = (t_vec < t_lst) ? "vector" : "list";
    cout << "| " << left << setw(35) << operation
         << "| " << right << setw(10) << fixed << setprecision(3) << t_vec << " ms "
         << "| " << right << setw(10) << fixed << setprecision(3) << t_lst << " ms "
         << "| " << left << setw(10) << vainqueur << " |" << endl;
}

int main() {
    cout << "==============================================================================\n";
    cout << "  BENCHMARK WORST-CASE : std::vector vs std::list (FICHIER DE 200 000 LIGNES) \n";
    cout << "==============================================================================\n";
    cout << "| " << left << setw(35) << "Situation / Operation" 
         << "| " << setw(13) << "std::vector" 
         << "| " << setw(13) << "std::list" 
         << "| " << setw(10) << "Plus rapide" << " |" << endl;
    cout << "|------------------------------------|--------------|--------------|------------|\n";

    // -------------------------------------------------------------
    // 1. CHARGEMENT DU GROS FICHIER (200 000 entiers)
    // -------------------------------------------------------------
    string input_file = resolve_input_path("data.txt");
    vector<int> v;
    list<int> l;
    int val;

    auto t1 = high_resolution_clock::now();
    ifstream f_vec(input_file);
    while (f_vec >> val) v.push_back(val);
    f_vec.close();
    auto t2 = high_resolution_clock::now();
    double t_load_vec = get_ms(t1, t2);

    t1 = high_resolution_clock::now();
    ifstream f_lst(input_file);
    while (f_lst >> val) l.push_back(val);
    f_lst.close();
    t2 = high_resolution_clock::now();
    double t_load_lst = get_ms(t1, t2);

    print_row("1. Chargement fichier (200k lignes)", t_load_vec, t_load_lst);

    // -------------------------------------------------------------
    // 2. INSERTION AU DEBUT (Worst Case pour Vector : 1 000 insertions)
    // -------------------------------------------------------------
    // Vector doit décaler 200 000 éléments à chaque fois (200k * 1 000 = 200 millions de décalages)
    // List crée un nœud en O(1) et met à jour 2 pointeurs
    t1 = high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        v.insert(v.begin(), i);
    }
    t2 = high_resolution_clock::now();
    double t_ins_front_vec = get_ms(t1, t2);

    t1 = high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        l.push_front(i);
    }
    t2 = high_resolution_clock::now();
    double t_ins_front_lst = get_ms(t1, t2);

    print_row("2. Insertion debut (1 000 x front)", t_ins_front_vec, t_ins_front_lst);

    // -------------------------------------------------------------
    // 3. INSERTION AU MILIEU (500 insertions)
    // -------------------------------------------------------------
    // Vector : accès direct au centre en O(1), décalage de la 2nde moitié
    // List : doit traverser 100 000 pointeurs pour arriver au milieu
    t1 = high_resolution_clock::now();
    for (int i = 0; i < 500; ++i) {
        v.insert(v.begin() + (v.size() / 2), 777);
    }
    t2 = high_resolution_clock::now();
    double t_ins_mid_vec = get_ms(t1, t2);

    t1 = high_resolution_clock::now();
    for (int i = 0; i < 500; ++i) {
        auto it = l.begin();
        advance(it, l.size() / 2); // Parcours séquentiel de 100k pointeurs à chaque fois
        l.insert(it, 777);
    }
    t2 = high_resolution_clock::now();
    double t_ins_mid_lst = get_ms(t1, t2);

    print_row("3. Insertion milieu (500 elements)", t_ins_mid_vec, t_ins_mid_lst);

    // -------------------------------------------------------------
    // 4. INSERTION A LA FIN (10 000 insertions à la suite)
    // -------------------------------------------------------------
    t1 = high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) {
        v.push_back(i);
    }
    t2 = high_resolution_clock::now();
    double t_ins_back_vec = get_ms(t1, t2);

    t1 = high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) {
        l.push_back(i);
    }
    t2 = high_resolution_clock::now();
    double t_ins_back_lst = get_ms(t1, t2);

    print_row("4. Insertion fin (10 000 x back)", t_ins_back_vec, t_ins_back_lst);

    // -------------------------------------------------------------
    // 5. AUGMENTATION DE TAILLE (resize +50 000 elements)
    // -------------------------------------------------------------
    // Vector : reallocation d'un seul bloc contigu en memoire + memset / initialisation
    // List : 50 000 allocations individuelles sur le tas (heap) + mise a jour des pointeurs
    t1 = high_resolution_clock::now();
    v.resize(v.size() + 50000, 0);
    t2 = high_resolution_clock::now();
    double t_resize_vec = get_ms(t1, t2);

    t1 = high_resolution_clock::now();
    l.resize(l.size() + 50000, 0);
    t2 = high_resolution_clock::now();
    double t_resize_lst = get_ms(t1, t2);

    print_row("5. Augmenter taille (resize +50k)", t_resize_vec, t_resize_lst);

    // -------------------------------------------------------------
    // 6. RECHERCHE WORST-CASE (Élément inexistant : scanne TOUT le conteneur 20 fois)
    // -------------------------------------------------------------
    // Le worst-case absolu pour une recherche est un élément qui n'existe pas :
    // l'algorithme est forcé de parcourir l'intégralité des éléments jusqu'au bout.
    const int VALEUR_INEXISTANTE = -999999;
    volatile int dummy = 0;

    t1 = high_resolution_clock::now();
    for (int rep = 0; rep < 20; ++rep) {
        auto it = find(v.begin(), v.end(), VALEUR_INEXISTANTE);
        if (it == v.end()) dummy = dummy + 1;
    }
    t2 = high_resolution_clock::now();
    double t_find_vec = get_ms(t1, t2);

    t1 = high_resolution_clock::now();
    for (int rep = 0; rep < 20; ++rep) {
        auto it = find(l.begin(), l.end(), VALEUR_INEXISTANTE);
        if (it == l.end()) dummy = dummy + 1;
    }
    t2 = high_resolution_clock::now();
    double t_find_lst = get_ms(t1, t2);

    print_row("6. Recherche worst-case (non trouve)", t_find_vec, t_find_lst);

    // -------------------------------------------------------------
    // 7. MISE A JOUR MASSIVE (Update réel avec itérateurs sur tous les éléments)
    // -------------------------------------------------------------
    // Parcourt les éléments avec itérateurs et met à jour chaque valeur :
    // Vector : accès mémoire continue -> Cache L1/L2 hits massifs
    // List : saut de nœud en nœud -> Cache misses à répétition
    t1 = high_resolution_clock::now();
    for (auto it = v.begin(); it != v.end(); ++it) {
        if (*it % 2 == 0) {
            *it += 1; // Update
        }
    }
    t2 = high_resolution_clock::now();
    double t_update_vec = get_ms(t1, t2);

    t1 = high_resolution_clock::now();
    for (auto it = l.begin(); it != l.end(); ++it) {
        if (*it % 2 == 0) {
            *it += 1; // Update
        }
    }
    t2 = high_resolution_clock::now();
    double t_update_lst = get_ms(t1, t2);

    print_row("7. Mise a jour (Update items)", t_update_vec, t_update_lst);

    // -------------------------------------------------------------
    // 8. SUPPRESSION WORST-CASE (1 000 suppressions au tout début)
    // -------------------------------------------------------------
    // Vector : chaque erase(begin) décale plus de 200 000 éléments vers la gauche !
    // List : supprime le premier nœud en O(1) sans aucun décalage.
    t1 = high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        v.erase(v.begin());
    }
    t2 = high_resolution_clock::now();
    double t_del_front_vec = get_ms(t1, t2);

    t1 = high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        l.pop_front();
    }
    t2 = high_resolution_clock::now();
    double t_del_front_lst = get_ms(t1, t2);

    print_row("8. Suppression debut (1 000 x erase)", t_del_front_vec, t_del_front_lst);

    // -------------------------------------------------------------
    // 9. SAUVEGARDE DU RESULTAT
    // -------------------------------------------------------------
    string out_v_path = resolve_output_path("data_vector.txt");
    string out_l_path = resolve_output_path("data_list.txt");

    t1 = high_resolution_clock::now();
    ofstream out_v(out_v_path);
    for (int x : v) out_v << x << "\n";
    out_v.close();
    t2 = high_resolution_clock::now();
    double t_save_vec = get_ms(t1, t2);

    t1 = high_resolution_clock::now();
    ofstream out_l(out_l_path);
    for (int x : l) out_l << x << "\n";
    out_l.close();
    t2 = high_resolution_clock::now();
    double t_save_lst = get_ms(t1, t2);

    print_row("9. Sauvegarde fichier", t_save_vec, t_save_lst);

    cout << "==============================================================================\n";
    cout << "\nANALYSE DES CAS CRITIQUES (WORST-CASE) :\n";
    cout << "1. Insertion & Suppression en tete :\n";
    cout << "   - LIST ecrasante : O(1) instantane.\n";
    cout << "   - VECTOR catastrophique : O(N) avec des millions d'octets decales par iteration.\n\n";
    cout << "2. Insertion au milieu :\n";
    cout << "   - LIST catastrophique : advance(it, 100 000) oblige a parcourir 100 000 pointeurs !\n";
    cout << "   - VECTOR rapide : acces direct O(1) a l'indice grace aux iterateurs Random Access.\n\n";
    cout << "3. Augmentation de taille (resize) :\n";
    cout << "   - VECTOR nettement plus rapide : 1 seule allocation memoire contigue + initialisation en bloc.\n";
    cout << "   - LIST ralentie : allocation individuelle de chaque noeud sur le tas (50 000 x malloc).\n\n";
    cout << "4. Mise a jour (Update) & Recherche Worst-Case :\n";
    cout << "   - VECTOR nettement plus rapide : grace a la continuite memoire (L1 Cache Hit).\n";
    cout << "   - LIST ralentie par le surcout des allocations et des sauts de pointeurs (Cache Misses).\n";

    return 0;
}
