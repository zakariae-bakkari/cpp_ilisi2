// Exercice 1 : pile générique (tableau dynamique + liste chaînée)
#include <chrono>
#include <iostream>
#include <string>
#include "PileListe.h"
#include "PileTableau.h"
// Point n'est pas instancié dans libpile.so : on inclut l'implémentation
// pour que le compilateur génère PileTableau<Point> dans ce programme.
#include "PileTableau.tpp"
using namespace std;

// Type utilisateur pour montrer la généricité
struct Point {
    int x, y;
};

ostream& operator<<(ostream& os, const Point& p) {
    return os << "(" << p.x << "," << p.y << ")";
}

// Fonction cliente : ne connaît que l'interface Pile<T>
template <typename T>
void viderEtAfficher(Pile<T>& p) {
    cout << "  depilement :";
    while (!p.estVide())
        cout << " " << p.depiler();
    cout << endl;
}

template <class PileInt>
double mesurer(int n) {
    auto debut = chrono::steady_clock::now();
    PileInt p;
    for (int i = 0; i < n; i++)
        p.empiler(i);
    while (!p.estVide())
        p.depiler();
    auto fin = chrono::steady_clock::now();
    return chrono::duration<double, milli>(fin - debut).count();
}

int main() {
    cout << "=== 1. PileTableau<int> ===" << endl;
    PileTableau<int> pt(2);
    for (int i = 1; i <= 6; i++) {
        pt.empiler(i * 10);
        cout << "  empiler(" << i * 10 << ") -> taille=" << pt.taille()
             << " capacite=" << pt.getCapacite() << endl;
    }
    cout << "  contenu : "; pt.afficher(); cout << endl;
    cout << "  sommet  : " << pt.getSommet() << endl;
    cout << "  depiler : " << pt.depiler() << endl;
    cout << "  contenu : "; pt.afficher(); cout << endl;

    cout << "\n=== 2. PileListe<string> ===" << endl;
    PileListe<string> pl;
    pl.empiler("alpha");
    pl.empiler("beta");
    pl.empiler("gamma");
    cout << "  contenu : "; pl.afficher(); cout << endl;
    cout << "  sommet  : " << pl.getSommet() << endl;

    cout << "\n=== 3. PileTableau<Point> (type utilisateur) ===" << endl;
    PileTableau<Point> pp;
    pp.empiler({1, 2});
    pp.empiler({3, 4});
    cout << "  contenu : "; pp.afficher(); cout << endl;

    cout << "\n=== 4. Polymorphisme via Pile<T>& ===" << endl;
    PileTableau<char> pc;
    PileListe<char> lc;
    Pile<char>* piles[] = {&pc, &lc};
    for (Pile<char>* p : piles)
        for (char c : string("PILE"))
            p->empiler(c);
    cout << "PileTableau<char>" << endl; viderEtAfficher(pc);
    cout << "PileListe<char>" << endl;   viderEtAfficher(lc);

    cout << "\n=== 5. Copie profonde ===" << endl;
    PileListe<int> original;
    original.empiler(1);
    original.empiler(2);
    PileListe<int> copie = original;
    copie.empiler(99);
    cout << "  original : "; original.afficher(); cout << endl;
    cout << "  copie    : "; copie.afficher(); cout << endl;
    PileTableau<int> t1, t2;
    t1.empiler(5);
    t2 = t1;
    t2.empiler(6);
    cout << "  t1 : "; t1.afficher(); cout << "   t2 : "; t2.afficher(); cout << endl;

    cout << "\n=== 6. Exceptions (pile vide) ===" << endl;
    try {
        PileTableau<int> vide;
        vide.depiler();
    } catch (const underflow_error& e) {
        cout << "  PileTableau : " << e.what() << endl;
    }
    try {
        PileListe<int> vide;
        vide.getSommet();
    } catch (const underflow_error& e) {
        cout << "  PileListe   : " << e.what() << endl;
    }

    cout << "\n=== 7. Performance (empiler puis depiler n entiers) ===" << endl;
    for (int n : {100000, 1000000, 10000000}) {
        double a = mesurer<PileTableau<int>>(n);
        double b = mesurer<PileListe<int>>(n);
        cout << "  n=" << n << "\tTableau: " << a << " ms\tListe: " << b << " ms" << endl;
    }
    return 0;
}
