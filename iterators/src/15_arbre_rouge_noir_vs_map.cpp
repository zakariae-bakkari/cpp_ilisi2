#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

// ==============================================================================
// NOTRE ARBRE ROUGE-NOIR (fait main) VS std::map VS std::unordered_map
// ==============================================================================
// Temps d'insertion, de recherche (cles presentes / absentes), de parcours et
// de suppression, pour 100 000 et 10 000 000 cles, avec des donnees
// aleatoires, triees et partiellement triees.
//   - std::map           : arbre rouge-noir de la STL -> O(log n), cles triees
//   - std::unordered_map : table de hachage           -> O(1) en moyenne, pas d'ordre

// ------------------------------------------------------------------------------
// Notre arbre rouge-noir (meme code que 14, plus la suppression)
// ------------------------------------------------------------------------------

struct Noeud {
    int cle;
    bool rouge;                       // true = rouge, false = noir
    Noeud *gauche, *droite, *parent;  // nullptr = feuille nil (noire)
};

bool estRouge(Noeud* n) { return n != nullptr && n->rouge; }  // nil = noir

// v prend la place de u chez le parent de u (v peut etre nil)
void remplacer(Noeud*& racine, Noeud* u, Noeud* v) {
    if (u->parent == nullptr) racine = v;
    else if (u == u->parent->gauche) u->parent->gauche = v;
    else u->parent->droite = v;
    if (v) v->parent = u->parent;
}

void rotationGauche(Noeud*& racine, Noeud* x) {  // x descend a gauche
    Noeud* y = x->droite;
    x->droite = y->gauche;
    if (y->gauche) y->gauche->parent = x;
    remplacer(racine, x, y);
    y->gauche = x;
    x->parent = y;
}

void rotationDroite(Noeud*& racine, Noeud* x) {  // x descend a droite
    Noeud* y = x->gauche;
    x->gauche = y->droite;
    if (y->droite) y->droite->parent = x;
    remplacer(racine, x, y);
    y->droite = x;
    x->parent = y;
}

// ---- Insertion ----
void reparerInsertion(Noeud*& racine, Noeud* n) {
    while (estRouge(n->parent)) {
        Noeud* p = n->parent;
        Noeud* g = p->parent;              // existe : un parent rouge n'est pas la racine
        bool pGauche = (p == g->gauche);   // false = cas miroir
        Noeud* oncle = pGauche ? g->droite : g->gauche;

        if (estRouge(oncle)) {             // oncle rouge : recoloration
            p->rouge = oncle->rouge = false;
            g->rouge = true;
            n = g;                         // on remonte
            continue;
        }
        if (n == (pGauche ? p->droite : p->gauche)) {  // zig-zag -> ligne
            pGauche ? rotationGauche(racine, p) : rotationDroite(racine, p);
            n = p;
            p = n->parent;
        }
        pGauche ? rotationDroite(racine, g) : rotationGauche(racine, g);  // ligne
        p->rouge = false;
        g->rouge = true;
    }
    racine->rouge = false;                 // la racine est toujours noire
}

void inserer(Noeud*& racine, int cle) {
    Noeud *parent = nullptr, *courant = racine;
    while (courant != nullptr) {           // descente comme dans un ABR
        if (cle == courant->cle) return;   // deja present
        parent = courant;
        courant = (cle < courant->cle) ? courant->gauche : courant->droite;
    }
    Noeud* n = new Noeud{cle, true, nullptr, nullptr, parent};
    if (parent == nullptr) racine = n;
    else if (cle < parent->cle) parent->gauche = n;
    else parent->droite = n;
    reparerInsertion(racine, n);
}

bool rechercher(Noeud* n, int cle) {
    while (n != nullptr && n->cle != cle) n = (cle < n->cle) ? n->gauche : n->droite;
    return n != nullptr;
}

// ---- Suppression ----
// Si on retire un noeud NOIR, un chemin perd un noir : x porte alors un
// "noir en trop" qu'il faut replacer. On regarde le frere f de x :
//   cas 1 : f rouge                     -> rotation au parent, f devient noir
//   cas 2 : f noir, deux neveux noirs   -> f rouge, le probleme remonte au parent
//   cas 3 : f noir, neveu proche rouge  -> rotation en f (le rouge passe loin)
//   cas 4 : f noir, neveu loin rouge    -> rotation au parent, fini
// x peut etre nil, donc on garde aussi son parent.
void reparerSuppression(Noeud*& racine, Noeud* x, Noeud* parent) {
    while (x != racine && !estRouge(x)) {
        bool xGauche = (x == parent->gauche);
        Noeud* f = xGauche ? parent->droite : parent->gauche;
        if (estRouge(f)) {                                         // cas 1
            f->rouge = false;
            parent->rouge = true;
            xGauche ? rotationGauche(racine, parent) : rotationDroite(racine, parent);
            f = xGauche ? parent->droite : parent->gauche;
        }
        Noeud* proche = xGauche ? f->gauche : f->droite;
        Noeud* loin = xGauche ? f->droite : f->gauche;
        if (!estRouge(proche) && !estRouge(loin)) {                // cas 2
            f->rouge = true;
            x = parent;
            parent = x->parent;
            continue;
        }
        if (!estRouge(loin)) {                                     // cas 3
            proche->rouge = false;
            f->rouge = true;
            xGauche ? rotationDroite(racine, f) : rotationGauche(racine, f);
            f = xGauche ? parent->droite : parent->gauche;
            loin = xGauche ? f->droite : f->gauche;
        }
        f->rouge = parent->rouge;                                  // cas 4
        parent->rouge = false;
        loin->rouge = false;
        xGauche ? rotationGauche(racine, parent) : rotationDroite(racine, parent);
        x = racine;
    }
    if (x) x->rouge = false;
}

bool supprimer(Noeud*& racine, int cle) {
    Noeud* z = racine;                     // 1) trouver le noeud
    while (z != nullptr && z->cle != cle) z = (cle < z->cle) ? z->gauche : z->droite;
    if (z == nullptr) return false;

    // 2) le retirer comme dans un ABR
    bool noirRetire = !z->rouge;
    Noeud *x, *xParent;
    if (z->gauche == nullptr || z->droite == nullptr) {   // 0 ou 1 enfant
        x = z->gauche ? z->gauche : z->droite;
        xParent = z->parent;
        remplacer(racine, z, x);
    } else {                               // 2 enfants : le successeur y prend sa place
        Noeud* y = z->droite;
        while (y->gauche) y = y->gauche;
        noirRetire = !y->rouge;
        x = y->droite;
        xParent = y;
        if (y->parent != z) {
            xParent = y->parent;
            remplacer(racine, y, y->droite);
            y->droite = z->droite;
            y->droite->parent = y;
        }
        remplacer(racine, z, y);
        y->gauche = z->gauche;
        y->gauche->parent = y;
        y->rouge = z->rouge;
    }
    delete z;

    // 3) reparer si un noir a disparu
    if (noirRetire) reparerSuppression(racine, x, xParent);
    return true;
}

// ---- Outils ----
int hauteur(Noeud* n) { return n ? 1 + max(hauteur(n->gauche), hauteur(n->droite)) : 0; }

void parcours(Noeud* n, long long& somme) {  // ordre croissant
    if (n == nullptr) return;
    parcours(n->gauche, somme);
    somme += n->cle;
    parcours(n->droite, somme);
}

// Renvoie la hauteur noire, ou -1 si une regle est violee
int hauteurNoire(Noeud* n) {
    if (n == nullptr) return 1;
    if (n->rouge && (estRouge(n->gauche) || estRouge(n->droite))) return -1;
    if (n->gauche && (n->gauche->parent != n || n->gauche->cle >= n->cle)) return -1;
    if (n->droite && (n->droite->parent != n || n->droite->cle <= n->cle)) return -1;
    int g = hauteurNoire(n->gauche), d = hauteurNoire(n->droite);
    if (g < 0 || g != d) return -1;
    return g + (n->rouge ? 0 : 1);
}

bool valide(Noeud* racine) { return racine == nullptr || (!racine->rouge && hauteurNoire(racine) > 0); }

void liberer(Noeud* n) {
    if (n == nullptr) return;
    liberer(n->gauche);
    liberer(n->droite);
    delete n;
}

// ------------------------------------------------------------------------------
// Test de correction : operations au hasard, comparees a std::set
// ------------------------------------------------------------------------------
bool testCorrection() {
    mt19937 gen(7);
    Noeud* racine = nullptr;
    set<int> reference;
    for (int i = 0; i < 200000; i++) {
        int cle = gen() % 5000;
        if (gen() % 2) { inserer(racine, cle); reference.insert(cle); }
        else if (supprimer(racine, cle) != (reference.erase(cle) == 1)) return false;
        if (i % 1000 == 0 && !valide(racine)) return false;
    }
    long long somme = 0, sommeRef = 0;
    parcours(racine, somme);
    for (int c : reference) sommeRef += c;
    liberer(racine);
    return somme == sommeRef;
}

// ------------------------------------------------------------------------------
// Mesures
// ------------------------------------------------------------------------------

template <class F> double ms(F f) {
    auto t0 = high_resolution_clock::now();
    f();
    return duration<double, milli>(high_resolution_clock::now() - t0).count();
}

// Le resultat du parcours est ecrit ici : sans ca, le compilateur supprime
// la boucle (la somme ne servirait a rien) et on mesurerait 0 ms.
volatile long long puits;

struct Temps { double insertion, presents, absents, parcours, suppression; long long trouves; int hauteur; };

// Insertion, recherche, parcours puis suppression de toutes les cles
Temps mesurerNotreArbre(const vector<int>& cles, const vector<int>& absents) {
    Temps t{};
    Noeud* racine = nullptr;
    long long somme = 0;
    t.insertion = ms([&] { for (int c : cles) inserer(racine, c); });
    t.presents = ms([&] { for (int c : cles) t.trouves += rechercher(racine, c); });
    t.absents = ms([&] { for (int c : absents) t.trouves += rechercher(racine, c); });
    t.parcours = ms([&] { parcours(racine, somme); puits = somme; });
    t.hauteur = hauteur(racine);
    if (!valide(racine)) cout << "ERREUR : arbre invalide apres insertion\n";
    t.suppression = ms([&] { for (int c : cles) supprimer(racine, c); });
    if (racine != nullptr) cout << "ERREUR : arbre non vide apres suppression\n";
    return t;
}

template <class M>
Temps mesurerSTL(const vector<int>& cles, const vector<int>& absents) {
    Temps t{};
    t.hauteur = -1;
    M m;
    long long somme = 0;
    t.insertion = ms([&] { for (int c : cles) m.emplace(c, c); });
    t.presents = ms([&] { for (int c : cles) t.trouves += (m.find(c) != m.end()); });
    t.absents = ms([&] { for (int c : absents) t.trouves += (m.find(c) != m.end()); });
    t.parcours = ms([&] { for (auto& kv : m) somme += kv.first; puits = somme; });
    t.suppression = ms([&] { for (int c : cles) m.erase(c); });
    if (!m.empty()) cout << "ERREUR : conteneur non vide apres suppression\n";
    return t;
}

// Temps avec son unite : "38.8 ms" sous une seconde, "23.38 s" au-dessus
string duree(double ms) {
    ostringstream s;
    s << fixed;
    if (ms < 1000) s << setprecision(1) << ms << " ms";
    else s << setprecision(2) << ms / 1000 << " s ";
    return s.str();
}

void ligne(const string& donnees, const string& nom, const Temps& t, size_t n) {
    double total = t.insertion + t.presents + t.absents + t.parcours + t.suppression;
    cout << "| " << left << setw(10) << donnees << " | " << setw(18) << nom << right;
    for (double d : {t.insertion, t.presents, t.absents, t.parcours, t.suppression, total})
        cout << " | " << setw(11) << duree(d);
    cout << " | " << setw(7) << (t.hauteur < 0 ? "-" : to_string(t.hauteur)) << " |" << endl;
    if (t.trouves != (long long)n) cout << "ERREUR : recherche incorrecte pour " << nom << "\n";
}

// n valeurs depart, depart+2, depart+4, ... rangees selon le type :
//   "aleatoire" : melangees
//   "triee"     : dans l'ordre croissant
//   "partielle" : croissantes, puis 10 % des valeurs echangees au hasard
vector<int> generer(int n, int depart, const string& type, mt19937& gen) {
    vector<int> v(n);
    for (int i = 0; i < n; i++) v[i] = depart + 2 * i;
    if (type == "aleatoire") shuffle(v.begin(), v.end(), gen);
    if (type == "partielle")
        for (int k = 0; k < n / 10; k++) swap(v[gen() % n], v[gen() % n]);
    return v;
}

void comparer(int n) {
    string sep = "+------------+--------------------+-------------+-------------+-------------+-------------+-------------+-------------+---------+\n";
    cout << "\n=== n = " << n << " cles ===\n" << sep
         << "| Donnees    | Structure          |   Insertion |    Rech. OK |    Rech. KO |    Parcours | Suppression |       Total | Hauteur |\n"
         << sep;
    mt19937 gen(2026);
    for (string type : {"aleatoire", "triee", "partielle"}) {
        vector<int> cles = generer(n, 2, type, gen);     // pairs : presents
        vector<int> absents = generer(n, 1, type, gen);  // impairs : absents
        ligne(type, "Notre arbre RN", mesurerNotreArbre(cles, absents), n);
        ligne(type, "std::map", mesurerSTL<map<int, int>>(cles, absents), n);
        ligne(type, "std::unordered_map", mesurerSTL<unordered_map<int, int>>(cles, absents), n);
        cout << sep;
    }
    cout << "Borne de hauteur 2*log2(n+1) = " << fixed << setprecision(1) << 2 * log2(n + 1.0) << "\n";
}

int main() {
    cout << "Test de correction (200 000 operations au hasard vs std::set) : "
         << (testCorrection() ? "OK" : "ECHEC") << "\n"
         << "Rech. OK = recherche des n cles presentes, Rech. KO = n cles absentes.\n"
         << "Parcours : ordre croissant pour l'arbre et map, ordre quelconque pour unordered_map.\n"
         << "Suppression : toutes les cles, dans l'ordre d'insertion.\n"
         << "(10 000 000 de cles : compter plusieurs minutes)\n";
    comparer(100000);
    comparer(10000000);
    return 0;
}
