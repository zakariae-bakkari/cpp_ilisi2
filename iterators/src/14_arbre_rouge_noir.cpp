#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

// ==============================================================================
// ARBRE ROUGE-NOIR : INSERTION, RECHERCHE, HAUTEUR ET TEMPS
// ==============================================================================
//
// Regles : la racine est noire, un rouge n'a pas d'enfant rouge, et tous les
// chemins vers les feuilles ont le meme nombre de noirs.
//
// Insertion : on insere comme dans un ABR, le nouveau noeud est ROUGE, puis
// tant que son parent est rouge on regarde l'oncle :
//   oncle rouge         -> recoloration, puis on remonte au grand-pere
//   oncle noir, zig-zag -> rotation au parent pour avoir une ligne
//   oncle noir, ligne   -> rotation au grand-pere + echange des couleurs

// Couleurs du terminal
const string FOND_ROUGE = "\033[41;97;1m";
const string FOND_NOIR  = "\033[100;97;1m";
const string RESET      = "\033[0m";

struct Noeud {
    int cle;
    bool rouge = true;          // un nouveau noeud est toujours rouge
    Noeud* gauche = nullptr;    // nullptr = feuille nil (noire)
    Noeud* droite = nullptr;
    Noeud* parent = nullptr;
};

class ArbreRN {
public:
    Noeud* racine = nullptr;

    ~ArbreRN() { liberer(racine); }

    void inserer(int cle) {
        // 1) Descente comme dans un ABR
        Noeud* parent = nullptr;
        Noeud* courant = racine;
        while (courant != nullptr) {
            parent = courant;
            if (cle < courant->cle) courant = courant->gauche;
            else if (cle > courant->cle) courant = courant->droite;
            else return;  // deja present
        }

        // 2) Accrocher le nouveau noeud (rouge)
        Noeud* n = new Noeud{cle};
        n->parent = parent;
        if (parent == nullptr) racine = n;
        else if (cle < parent->cle) parent->gauche = n;
        else parent->droite = n;

        // 3) Reparer
        reparer(n);
    }

    bool rechercher(int cle) const {
        Noeud* courant = racine;
        while (courant != nullptr) {
            if (cle == courant->cle) return true;
            courant = (cle < courant->cle) ? courant->gauche : courant->droite;
        }
        return false;
    }

    int hauteur() const { return hauteur(racine); }

private:
    static bool estRouge(Noeud* n) { return n != nullptr && n->rouge; }  // nil = noir

    void reparer(Noeud* n) {
        while (estRouge(n->parent)) {
            Noeud* p = n->parent;
            Noeud* g = p->parent;   // existe car un parent rouge n'est pas la racine

            if (p == g->gauche) {
                Noeud* oncle = g->droite;
                if (estRouge(oncle)) {            // oncle rouge : recoloration
                    p->rouge = false;
                    oncle->rouge = false;
                    g->rouge = true;
                    n = g;                        // on remonte
                } else {
                    if (n == p->droite) {         // zig-zag : on le met en ligne
                        rotationGauche(p);
                        n = p;
                        p = n->parent;
                    }
                    rotationDroite(g);            // ligne : rotation au grand-pere
                    p->rouge = false;
                    g->rouge = true;
                }
            } else {                              // meme chose en miroir
                Noeud* oncle = g->gauche;
                if (estRouge(oncle)) {
                    p->rouge = false;
                    oncle->rouge = false;
                    g->rouge = true;
                    n = g;
                } else {
                    if (n == p->gauche) {
                        rotationDroite(p);
                        n = p;
                        p = n->parent;
                    }
                    rotationGauche(g);
                    p->rouge = false;
                    g->rouge = true;
                }
            }
        }
        racine->rouge = false;  // la racine est toujours noire
    }

    // x descend a gauche, son fils droit y prend sa place
    void rotationGauche(Noeud* x) {
        Noeud* y = x->droite;
        x->droite = y->gauche;
        if (y->gauche) y->gauche->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) racine = y;
        else if (x == x->parent->gauche) x->parent->gauche = y;
        else x->parent->droite = y;
        y->gauche = x;
        x->parent = y;
    }

    // x descend a droite, son fils gauche y prend sa place
    void rotationDroite(Noeud* x) {
        Noeud* y = x->gauche;
        x->gauche = y->droite;
        if (y->droite) y->droite->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) racine = y;
        else if (x == x->parent->droite) x->parent->droite = y;
        else x->parent->gauche = y;
        y->droite = x;
        x->parent = y;
    }

    int hauteur(Noeud* n) const {
        if (n == nullptr) return 0;
        return 1 + max(hauteur(n->gauche), hauteur(n->droite));
    }

    void liberer(Noeud* n) {
        if (n == nullptr) return;
        liberer(n->gauche);
        liberer(n->droite);
        delete n;
    }
};

// ==============================================================================
// Affichage
// ==============================================================================

// Une case de tableau coloree, de largeur fixe
void caseCouleur(int cle, bool rouge, int largeur = 5) {
    cout << (rouge ? FOND_ROUGE : FOND_NOIR) << setw(largeur) << cle << " " << RESET << "|";
}

string texte(Noeud* n) { return n ? to_string(n->cle) : "nil"; }

// Tableau de depart : les valeurs dans l'ordre d'insertion.
// Chaque noeud est ROUGE au moment ou on l'insere.
void afficherDepart(const vector<int>& valeurs) {
    cout << "\nTABLEAU DE DEPART (ordre d'insertion, chaque nouveau noeud est rouge)\n";
    cout << "|";
    for (int v : valeurs) caseCouleur(v, true);
    cout << "\n";
}

// Tableau final : les noeuds niveau par niveau (parcours en largeur)
void afficherFin(const ArbreRN& a) {
    cout << "\nTABLEAU FINAL (arbre rouge-noir, niveau par niveau)\n";
    cout << "+--------+-------+---------+--------+--------+--------+\n";
    cout << "| Niveau | Noeud | Couleur | Parent | Gauche | Droite |\n";
    cout << "+--------+-------+---------+--------+--------+--------+\n";
    queue<pair<Noeud*, int>> file;
    file.push({a.racine, 0});
    while (!file.empty()) {
        auto [n, niveau] = file.front();
        file.pop();
        cout << "| " << setw(6) << niveau << " |";
        caseCouleur(n->cle, n->rouge, 6);
        cout << " " << left << setw(7) << (n->rouge ? "rouge" : "noir") << " | "
             << setw(6) << texte(n->parent) << " | "
             << setw(6) << texte(n->gauche) << " | "
             << setw(6) << texte(n->droite) << " |" << right << "\n";
        if (n->gauche) file.push({n->gauche, niveau + 1});
        if (n->droite) file.push({n->droite, niveau + 1});
    }
    cout << "+--------+-------+---------+--------+--------+--------+\n";

    // La meme chose sur une ligne, dans l'ordre croissant
    cout << "\nTABLEAU FINAL (ordre croissant, avec les couleurs)\n|";
    vector<Noeud*> pile;
    Noeud* c = a.racine;
    while (c || !pile.empty()) {
        while (c) { pile.push_back(c); c = c->gauche; }
        c = pile.back();
        pile.pop_back();
        caseCouleur(c->cle, c->rouge);
        c = c->droite;
    }
    cout << "\n";
}

// ==============================================================================
// Mesures
// ==============================================================================

struct Resultat {
    string nom;
    size_t n;
    double insertion_ms, recherche_ms;
    int hauteur;
    size_t trouves;
};

Resultat mesurer(const string& nom, const vector<int>& valeurs, ArbreRN& a) {
    auto t0 = high_resolution_clock::now();
    for (int v : valeurs) a.inserer(v);
    auto t1 = high_resolution_clock::now();

    size_t trouves = 0;
    for (int v : valeurs) trouves += a.rechercher(v);
    auto t2 = high_resolution_clock::now();

    return {nom, valeurs.size(),
            duration<double, milli>(t1 - t0).count(),
            duration<double, milli>(t2 - t1).count(),
            a.hauteur(), trouves};
}

// n valeurs distinctes de 1 a n, melangees
vector<int> valeursMelangees(int n) {
    vector<int> v(n);
    for (int i = 0; i < n; i++) v[i] = i + 1;
    shuffle(v.begin(), v.end(), mt19937(2026));
    return v;
}

int main() {
    vector<Resultat> resultats;

    // Cas 1 : 10 valeurs, on affiche les tableaux
    vector<int> dix = {1, 45, 67, 89, 12, 34, 23, 78, 56, 90};
    ArbreRN a10;
    resultats.push_back(mesurer("10 valeurs", dix, a10));
    afficherDepart(dix);
    afficherFin(a10);

    // Cas 2 et 3 : 1 000 et 100 000 valeurs melangees
    ArbreRN a1000, a100000;
    resultats.push_back(mesurer("1 000 valeurs", valeursMelangees(1000), a1000));
    resultats.push_back(mesurer("100 000 valeurs", valeursMelangees(100000), a100000));

    // Tableau des temps
    cout << "\nTEMPS ET HAUTEUR\n";
    string ligne = "+-----------------+---------+----------------+----------------+---------+---------------+---------+";
    cout << ligne << "\n";
    cout << "| Cas             |       n | Insertion (ms) | Recherche (ms) | Hauteur | 2*log2(n+1)   | Trouves |\n";
    cout << ligne << "\n";
    for (const Resultat& r : resultats) {
        cout << "| " << left << setw(15) << r.nom << " | " << right
             << setw(7) << r.n << " | "
             << fixed << setprecision(4) << setw(14) << r.insertion_ms << " | "
             << setw(14) << r.recherche_ms << " | "
             << setw(7) << r.hauteur << " | "
             << setprecision(1) << setw(13) << 2 * log2(r.n + 1.0) << " | "
             << setw(7) << r.trouves << " |\n";
    }
    cout << ligne << "\n";
    cout << "La hauteur reste toujours sous 2*log2(n+1) : l'arbre reste equilibre.\n";
    return 0;
}
