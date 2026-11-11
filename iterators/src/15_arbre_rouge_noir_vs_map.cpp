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
// de suppression, pour 100 000 cles, avec des donnees
// aleatoires, triees et partiellement triees.
// On compte aussi les comparaisons, rotations, recolorations et allocations.
//   - std::map           : arbre rouge-noir de la STL -> O(log n), cles triees
//   - std::unordered_map : table de hachage           -> O(1) en moyenne, pas d'ordre

// ------------------------------------------------------------------------------
// Notre arbre rouge-noir (meme code que 14, plus la suppression)
// ------------------------------------------------------------------------------

// ---- Compteurs (remis a zero avant chaque mesure) ----
long long comparaisons = 0, rotations = 0, recolorations = 0, allocations = 0;

bool egal(int a, int b) { comparaisons++; return a == b; }  // comparaison comptee
bool inf(int a, int b) { comparaisons++; return a < b; }    // comparaison comptee

struct Noeud {
    int cle;
    bool rouge;                       // true = rouge, false = noir
    Noeud *gauche, *droite, *parent;  // nullptr = feuille nil (noire)
};

bool estRouge(Noeud* n) { return n != nullptr && n->rouge; }  // nil = noir

// Change la couleur d'un noeud (comptee seulement si elle change vraiment)
void colorier(Noeud* n, bool rouge) {
    if (n->rouge != rouge) recolorations++;
    n->rouge = rouge;
}

// v prend la place de u chez le parent de u (v peut etre nil)
void remplacer(Noeud*& racine, Noeud* u, Noeud* v) {
    if (u->parent == nullptr) racine = v;
    else if (u == u->parent->gauche) u->parent->gauche = v;
    else u->parent->droite = v;
    if (v) v->parent = u->parent;
}

void rotationGauche(Noeud*& racine, Noeud* x) {  // x descend a gauche
    rotations++;
    Noeud* y = x->droite;
    x->droite = y->gauche;
    if (y->gauche) y->gauche->parent = x;
    remplacer(racine, x, y);
    y->gauche = x;
    x->parent = y;
}

void rotationDroite(Noeud*& racine, Noeud* x) {  // x descend a droite
    rotations++;
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
            colorier(p, false);
            colorier(oncle, false);
            colorier(g, true);
            n = g;                         // on remonte
            continue;
        }
        if (n == (pGauche ? p->droite : p->gauche)) {  // zig-zag -> ligne
            pGauche ? rotationGauche(racine, p) : rotationDroite(racine, p);
            n = p;
            p = n->parent;
        }
        pGauche ? rotationDroite(racine, g) : rotationGauche(racine, g);  // ligne
        colorier(p, false);
        colorier(g, true);
    }
    colorier(racine, false);                // la racine est toujours noire
}

void inserer(Noeud*& racine, int cle) {
    Noeud *parent = nullptr, *courant = racine;
    while (courant != nullptr) {           // descente comme dans un ABR
        if (egal(cle, courant->cle)) return;   // deja present
        parent = courant;
        courant = inf(cle, courant->cle) ? courant->gauche : courant->droite;
    }
    Noeud* n = new Noeud{cle, true, nullptr, nullptr, parent};
    allocations++;
    if (parent == nullptr) racine = n;
    else if (inf(cle, parent->cle)) parent->gauche = n;
    else parent->droite = n;
    reparerInsertion(racine, n);
}

bool rechercher(Noeud* n, int cle) {
    while (n != nullptr && !egal(n->cle, cle)) n = inf(cle, n->cle) ? n->gauche : n->droite;
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
            colorier(f, false);
            colorier(parent, true);
            xGauche ? rotationGauche(racine, parent) : rotationDroite(racine, parent);
            f = xGauche ? parent->droite : parent->gauche;
        }
        Noeud* proche = xGauche ? f->gauche : f->droite;
        Noeud* loin = xGauche ? f->droite : f->gauche;
        if (!estRouge(proche) && !estRouge(loin)) {                // cas 2
            colorier(f, true);
            x = parent;
            parent = x->parent;
            continue;
        }
        if (!estRouge(loin)) {                                     // cas 3
            colorier(proche, false);
            colorier(f, true);
            xGauche ? rotationDroite(racine, f) : rotationGauche(racine, f);
            f = xGauche ? parent->droite : parent->gauche;
            loin = xGauche ? f->droite : f->gauche;
        }
        colorier(f, parent->rouge);                                // cas 4
        colorier(parent, false);
        colorier(loin, false);
        xGauche ? rotationGauche(racine, parent) : rotationDroite(racine, parent);
        x = racine;
    }
    if (x) colorier(x, false);
}

bool supprimer(Noeud*& racine, int cle) {
    Noeud* z = racine;                     // 1) trouver le noeud
    while (z != nullptr && !egal(z->cle, cle)) z = inf(cle, z->cle) ? z->gauche : z->droite;
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
        colorier(y, z->rouge);
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

// Compteurs d'un test : -1 = impossible a compter (cache dans la STL)
struct Compteurs { long long compInsertion, compRecherche, compSuppression, rotations, recolorations, allocations; };

void remettreAZero() { comparaisons = rotations = recolorations = allocations = 0; }

// Pour la STL : un comparateur et un allocateur "espions" qui comptent leurs appels
struct InfCompte  { bool operator()(int a, int b) const { return inf(a, b); } };
struct EgalCompte { bool operator()(int a, int b) const { return egal(a, b); } };

template <class T> struct AllocCompte {
    using value_type = T;
    AllocCompte() = default;
    template <class U> AllocCompte(const AllocCompte<U>&) {}
    T* allocate(size_t k) { allocations++; return allocator<T>().allocate(k); }
    void deallocate(T* p, size_t k) { allocator<T>().deallocate(p, k); }
    template <class U> bool operator==(const AllocCompte<U>&) const { return true; }
    template <class U> bool operator!=(const AllocCompte<U>&) const { return false; }
};

using MapCompte = map<int, int, InfCompte, AllocCompte<pair<const int, int>>>;
using UMapCompte = unordered_map<int, int, hash<int>, EgalCompte, AllocCompte<pair<const int, int>>>;

// Insertion, recherche, parcours puis suppression de toutes les cles
// (les temps et les compteurs sont mesures en meme temps)
Temps mesurerNotreArbre(const vector<int>& cles, const vector<int>& absents, Compteurs& c) {
    Temps t{};
    Noeud* racine = nullptr;
    long long somme = 0;
    remettreAZero();
    t.insertion = ms([&] { for (int k : cles) inserer(racine, k); });
    c.compInsertion = comparaisons;
    comparaisons = 0;
    t.presents = ms([&] { for (int k : cles) t.trouves += rechercher(racine, k); });
    t.absents = ms([&] { for (int k : absents) t.trouves += rechercher(racine, k); });
    c.compRecherche = comparaisons;
    comparaisons = 0;
    t.parcours = ms([&] { parcours(racine, somme); puits = somme; });
    t.hauteur = hauteur(racine);
    if (!valide(racine)) cout << "ERREUR : arbre invalide apres insertion\n";
    t.suppression = ms([&] { for (int k : cles) supprimer(racine, k); });
    c.compSuppression = comparaisons;
    if (racine != nullptr) cout << "ERREUR : arbre non vide apres suppression\n";
    c.rotations = rotations;
    c.recolorations = recolorations;
    c.allocations = allocations;
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

// Compteurs pour la STL : on refait le test avec les versions "espions"
// (a part, pour ne pas ralentir la mesure des temps)
template <class M>
Compteurs compterSTL(const vector<int>& cles, const vector<int>& absents) {
    Compteurs c{};
    M m;
    remettreAZero();
    for (int k : cles) m.emplace(k, k);
    c.compInsertion = comparaisons;
    comparaisons = 0;
    for (int k : cles) puits = (m.find(k) != m.end());
    for (int k : absents) puits = (m.find(k) != m.end());
    c.compRecherche = comparaisons;
    comparaisons = 0;
    for (int k : cles) m.erase(k);
    c.compSuppression = comparaisons;
    c.rotations = c.recolorations = -1;
    c.allocations = allocations;
    return c;
}

// Grand nombre lisible : 1234567 -> "1 234 567" ; -1 -> "-"
string nombre(long long v) {
    if (v < 0) return "-";
    string s = to_string(v);
    for (int i = (int)s.size() - 3; i > 0; i -= 3) s.insert(i, " ");
    return s;
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
        cout << " | " << setw(13) << duree(d);
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

void afficherCompteurs(int n, const vector<pair<string, Compteurs>>& lignes) {
    string sep = "+------------+--------------------+--------------+--------------+--------------+------------+---------------+-------------+\n";
    cout << "\n=== Compteurs (n = " << n << " cles) ===\n" << sep
         << "| Donnees    | Structure          | Comparaisons | Comparaisons | Comparaisons |  Rotations | Recolorations | Allocations |\n"
         << "|            |                    |    insertion |    recherche |  suppression |            |               |             |\n"
         << sep;
    const char* noms[] = {"Notre arbre RN", "std::map", "std::unordered_map"};
    for (size_t i = 0; i < lignes.size(); i++) {
        const Compteurs& c = lignes[i].second;
        cout << "| " << left << setw(10) << lignes[i].first << " | " << setw(18) << noms[i % 3]
             << right << " | " << setw(12) << nombre(c.compInsertion)
             << " | " << setw(12) << nombre(c.compRecherche)
             << " | " << setw(12) << nombre(c.compSuppression)
             << " | " << setw(10) << nombre(c.rotations)
             << " | " << setw(13) << nombre(c.recolorations)
             << " | " << setw(11) << nombre(c.allocations) << " |\n";
        if (i % 3 == 2) cout << sep;
    }
}

void comparer(int n) {
    string sep = "+------------+--------------------+---------------+---------------+---------------+---------------+---------------+---------------+---------+\n";
    cout << "\n=== n = " << n << " cles ===\n" << sep
         << "| Donnees    | Structure          |     Insertion |     Recherche |     Recherche |      Parcours |   Suppression |         Total | Hauteur |\n"
         << "|            |                    |               |  cle presente |   cle absente |               |               |               |         |\n"
         << sep;
    mt19937 gen(2026);
    vector<pair<string, Compteurs>> compteurs;
    for (string type : {"aleatoire", "triee", "partielle"}) {
        vector<int> cles = generer(n, 2, type, gen);     // pairs : presents
        vector<int> absents = generer(n, 1, type, gen);  // impairs : absents
        Compteurs c;
        ligne(type, "Notre arbre RN", mesurerNotreArbre(cles, absents, c), n);
        compteurs.push_back({type, c});
        ligne(type, "std::map", mesurerSTL<map<int, int>>(cles, absents), n);
        compteurs.push_back({type, compterSTL<MapCompte>(cles, absents)});
        ligne(type, "std::unordered_map", mesurerSTL<unordered_map<int, int>>(cles, absents), n);
        compteurs.push_back({type, compterSTL<UMapCompte>(cles, absents)});
        cout << sep;
    }
    cout << "Borne de hauteur 2*log2(n+1) = " << fixed << setprecision(1) << 2 * log2(n + 1.0) << "\n";
    afficherCompteurs(n, compteurs);
}

int main() {
    cout << "Test de correction (200 000 operations au hasard vs std::set) : "
         << (testCorrection() ? "OK" : "ECHEC") << "\n"
         << "Recherche cle presente : on cherche les n cles inserees (toutes trouvees).\n"
         << "Recherche cle absente  : on cherche n cles qui ne sont pas dans la structure.\n"
         << "Parcours : ordre croissant pour l'arbre et map, ordre quelconque pour unordered_map.\n"
         << "Suppression : toutes les cles, dans l'ordre d'insertion.\n";
    comparer(100000);
    cout << "Comparaisons : comparaisons de cles (== ou <). Recolorations : changements de couleur.\n"
         << "Allocations : appels a l'allocateur (noeuds, + tableaux de cases pour unordered_map).\n"
         << "Rotations et recolorations de la STL : cachees dans la bibliotheque, impossibles a compter.\n";
    return 0;
}
