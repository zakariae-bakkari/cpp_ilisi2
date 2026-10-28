#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <deque>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <random>

using namespace std;
using namespace std::chrono;

// ==============================================================================
// BENCHMARK : RECHERCHE (DEBUT / MILIEU / FIN) SUR VECTOR, LIST ET PILE (STACK)
// ==============================================================================
// Un million de caractères sont insérés, dans le même ordre, dans les trois
// conteneurs. Un caractère "sentinelle" unique est placé au début, au milieu
// et à la fin de la séquence d'insertion, puis on chronomètre la recherche
// de chacun de ces trois caractères dans chaque conteneur.
//
// Particularité de la pile (std::stack) : elle n'offre NI itérateur NI find().
// La seule façon de "chercher" dedans est de dépiler (pop) depuis le sommet
// jusqu'à tomber sur la valeur recherchée. Le sommet de la pile correspond au
// DERNIER élément inséré (donc à la position "fin" de la séquence), et le fond
// de la pile correspond au PREMIER élément inséré (position "début"). La pile
// inverse donc complètement les résultats de vector/list : y chercher le début
// de la séquence coûte aussi cher que la vider presque entièrement.

double get_ms(time_point<high_resolution_clock> start, time_point<high_resolution_clock> end) {
    return duration<double, milli>(end - start).count();
}

void print_header() {
    cout << "\n================================================================================================\n";
    cout << "   BENCHMARK RECHERCHE : std::vector vs std::list vs std::stack (PILE) -- 1 000 000 caracteres\n";
    cout << "================================================================================================\n";
    cout << "| " << left << setw(28) << "Position recherchee"
         << "| " << setw(13) << "std::vector"
         << "| " << setw(13) << "std::list"
         << "| " << setw(13) << "pile (stack)"
         << "| " << setw(10) << "Vainqueur" << " |\n";
    cout << "|-----------------------------|--------------|--------------|--------------|------------|\n";
}

void print_result(const string& position, double t_vec, double t_lst, double t_pile) {
    string vainqueur = "vector";
    double best = t_vec;
    if (t_lst < best) { best = t_lst; vainqueur = "list"; }
    if (t_pile < best) { best = t_pile; vainqueur = "pile"; }

    cout << "| " << left << setw(28) << position
         << "| " << right << setw(10) << fixed << setprecision(3) << t_vec << " ms "
         << "| " << right << setw(10) << fixed << setprecision(3) << t_lst << " ms "
         << "| " << right << setw(10) << fixed << setprecision(3) << t_pile << " ms "
         << "| " << left << setw(10) << vainqueur << " |\n";
}

// Recherche lineaire classique (std::find) pour vector et list
template <typename Container>
double rechercher_find(const Container& c, char cible) {
    auto t1 = high_resolution_clock::now();
    auto it = find(c.begin(), c.end(), cible);
    auto t2 = high_resolution_clock::now();
    volatile bool trouve = (it != c.end());
    (void)trouve;
    return get_ms(t1, t2);
}

// Recherche dans une pile : on depile depuis le sommet jusqu'a trouver la cible.
// La pile est passee PAR VALEUR : la copie (necessaire pour ne pas detruire
// l'originale) se fait AVANT l'entree dans la fonction, donc hors chronometrage.
double rechercher_pile(stack<char> s, char cible) {
    auto t1 = high_resolution_clock::now();
    bool trouve = false;
    while (!s.empty()) {
        if (s.top() == cible) { trouve = true; break; }
        s.pop();
    }
    auto t2 = high_resolution_clock::now();
    (void)trouve;
    return get_ms(t1, t2);
}

int main() {
    const int N = 1000000; // Un million de caracteres
    const char SENTINELLE_DEBUT = '#'; // 1er caractere insere
    const char SENTINELLE_MILIEU = '@'; // caractere du milieu
    const char SENTINELLE_FIN = '%';    // dernier caractere insere

    // -------------------------------------------------------------------
    // GENERATION DES DONNEES : un million de lettres aleatoires (a-z),
    // avec les trois sentinelles placees aux positions voulues.
    // -------------------------------------------------------------------
    mt19937 rng(42);
    uniform_int_distribution<int> distLettre('a', 'z');

    vector<char> base(N);
    for (int i = 0; i < N; ++i) base[i] = static_cast<char>(distLettre(rng));
    base[0] = SENTINELLE_DEBUT;
    base[N / 2] = SENTINELLE_MILIEU;
    base[N - 1] = SENTINELLE_FIN;

    vector<char> v(base.begin(), base.end());
    list<char> l(base.begin(), base.end());
    // La pile est construite dans l'ordre d'insertion a partir d'une deque :
    // le dernier element de "base" devient le sommet de la pile.
    stack<char> pile_source(deque<char>(base.begin(), base.end()));

    print_header();

    double t_vec_debut = rechercher_find(v, SENTINELLE_DEBUT);
    double t_lst_debut = rechercher_find(l, SENTINELLE_DEBUT);
    double t_pile_debut = rechercher_pile(pile_source, SENTINELLE_DEBUT);
    print_result("1. Debut (1er insere)", t_vec_debut, t_lst_debut, t_pile_debut);

    double t_vec_milieu = rechercher_find(v, SENTINELLE_MILIEU);
    double t_lst_milieu = rechercher_find(l, SENTINELLE_MILIEU);
    double t_pile_milieu = rechercher_pile(pile_source, SENTINELLE_MILIEU);
    print_result("2. Milieu", t_vec_milieu, t_lst_milieu, t_pile_milieu);

    double t_vec_fin = rechercher_find(v, SENTINELLE_FIN);
    double t_lst_fin = rechercher_find(l, SENTINELLE_FIN);
    double t_pile_fin = rechercher_pile(pile_source, SENTINELLE_FIN);
    print_result("3. Fin (dernier insere)", t_vec_fin, t_lst_fin, t_pile_fin);

    cout << "================================================================================================\n";
    cout << "\n--- POURQUOI CES RESULTATS ? ---\n";
    cout << "1. std::vector et std::list : std::find() parcourt TOUJOURS depuis begin().\n";
    cout << "   - Chercher le DEBUT est quasi instantane (1 comparaison).\n";
    cout << "   - Chercher la FIN coute O(N) comparaisons : vector reste plus rapide grace a la\n";
    cout << "     contiguite memoire (cache CPU), list souffre des sauts de pointeurs (cache misses).\n\n";
    cout << "2. std::stack (pile) : AUCUN iterateur, AUCUN find(). La seule acces possible est le\n";
    cout << "   sommet (top/pop), donc la recherche DEPILE depuis le dernier element insere.\n";
    cout << "   - Chercher la FIN (= le sommet) est instantane : O(1), 1 seul pop.\n";
    cout << "   - Chercher le DEBUT (= le fond) est le PIRE cas : il faut depiler presque tout\n";
    cout << "     le million d'elements, O(N), pour atteindre le fond.\n";
    cout << "   => La pile INVERSE completement le comportement de vector/list : elle n'est adaptee\n";
    cout << "      qu'a un acces LIFO au sommet, jamais a une recherche arbitraire dans la structure.\n";

    return 0;
}
