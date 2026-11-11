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
// ARBRE ROUGE-NOIR (SANS CLASSE) : INSERTION, RECHERCHE, HAUTEUR ET TEMPS
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
    bool rouge;       // true = rouge, false = noir
    Noeud* gauche;    // nullptr = feuille nil (noire)
    Noeud* droite;
    Noeud* parent;
};

// ------------------------------------------------------------------------------
// Fonctions de base
// ------------------------------------------------------------------------------

bool estRouge(Noeud* n) { return n != nullptr && n->rouge; }  // nil = noir

// x descend a gauche, son fils droit y prend sa place
void rotationGauche(Noeud*& racine, Noeud* x) {
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
void rotationDroite(Noeud*& racine, Noeud* x) {
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

void reparer(Noeud*& racine, Noeud* n) {
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
                    rotationGauche(racine, p);
                    n = p;
                    p = n->parent;
                }
                rotationDroite(racine, g);    // ligne : rotation au grand-pere
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
                    rotationDroite(racine, p);
                    n = p;
                    p = n->parent;
                }
                rotationGauche(racine, g);
                p->rouge = false;
                g->rouge = true;
            }
        }
    }
    racine->rouge = false;  // la racine est toujours noire
}

void inserer(Noeud*& racine, int cle) {
    // 1) Descente comme dans un ABR
    Noeud* parent = nullptr;
    Noeud* courant = racine;
    while (courant != nullptr) {
        parent = courant;
        if (cle < courant->cle) courant = courant->gauche;
        else if (cle > courant->cle) courant = courant->droite;
        else return;  // deja present
    }

    // 2) Accrocher le nouveau noeud, toujours rouge
    Noeud* n = new Noeud{cle, true, nullptr, nullptr, parent};
    if (parent == nullptr) racine = n;
    else if (cle < parent->cle) parent->gauche = n;
    else parent->droite = n;

    // 3) Reparer
    reparer(racine, n);
}

bool rechercher(Noeud* racine, int cle) {
    Noeud* courant = racine;
    while (courant != nullptr) {
        if (cle == courant->cle) return true;
        courant = (cle < courant->cle) ? courant->gauche : courant->droite;
    }
    return false;
}

int hauteur(Noeud* n) {
    if (n == nullptr) return 0;
    return 1 + max(hauteur(n->gauche), hauteur(n->droite));
}

int taille(Noeud* n) {
    if (n == nullptr) return 0;
    return 1 + taille(n->gauche) + taille(n->droite);
}

void liberer(Noeud* n) {
    if (n == nullptr) return;
    liberer(n->gauche);
    liberer(n->droite);
    delete n;
}

// ------------------------------------------------------------------------------
// Affichage
// ------------------------------------------------------------------------------

// Une case de tableau coloree, de largeur fixe
void caseCouleur(int cle, bool rouge, int largeur = 5) {
    cout << (rouge ? FOND_ROUGE : FOND_NOIR) << setw(largeur) << cle << " " << RESET << "|";
}

string texte(Noeud* n) { return n ? to_string(n->cle) : "nil"; }

// Tableau de depart : les valeurs dans l'ordre d'insertion.
// Chaque noeud est ROUGE au moment ou on l'insere.
void afficherDepart(const vector<int>& valeurs) {
    cout << "\nTABLEAU DE DEPART (ordre d'insertion, chaque nouveau noeud est rouge)\n|";
    for (int v : valeurs) caseCouleur(v, true);
    cout << "\n";
}

// ---- Dessin de l'arbre en couleur ----
// Chaque noeud occupe une case de LARGEUR colonnes. La colonne d'un noeud est
// donnee par son rang dans l'ordre croissant, donc les gauches sont a gauche.
// Ligne 2*profondeur : les noeuds ; ligne juste en dessous : les / et \.
const int LARGEUR = 4;

// grille : les caracteres ; couleur : 0 = rien, 1 = rouge, 2 = noir
int placer(Noeud* n, int prof, int& rang, vector<string>& grille,
           vector<vector<int>>& couleur) {
    if (n == nullptr) return -1;
    int colG = placer(n->gauche, prof + 1, rang, grille, couleur);
    int col = rang * LARGEUR;
    rang++;
    int colD = placer(n->droite, prof + 1, rang, grille, couleur);

    int ligne = 2 * prof;
    string s = to_string(n->cle);
    int debut = col + (LARGEUR - (int)s.size()) / 2;
    for (int k = 0; k < LARGEUR; k++) couleur[ligne][col + k] = n->rouge ? 1 : 2;
    for (int k = 0; k < (int)s.size(); k++) grille[ligne][debut + k] = s[k];

    if (colG >= 0) {  // branche gauche : ___ puis /
        int x = colG + LARGEUR / 2;
        grille[ligne + 1][x] = '/';
        for (int c = x + 1; c < col; c++) grille[ligne][c] = '_';
    }
    if (colD >= 0) {  // branche droite : ___ puis '\'
        int x = colD + LARGEUR / 2 - 1;
        grille[ligne + 1][x] = '\\';
        for (int c = col + LARGEUR; c < x; c++) grille[ligne][c] = '_';
    }
    return col;
}

void dessinerArbre(Noeud* racine) {
    cout << "\nARBRE FINAL (rouge = noeud rouge, gris = noeud noir)\n\n";
    int lignes = 2 * hauteur(racine) - 1;  // pas de branches sous le dernier niveau
    int colonnes = taille(racine) * LARGEUR;
    vector<string> grille(lignes, string(colonnes, ' '));
    vector<vector<int>> couleur(lignes, vector<int>(colonnes, 0));
    int rang = 0;
    placer(racine, 0, rang, grille, couleur);

    for (int l = 0; l < lignes; l++) {
        int actuelle = 0;
        cout << "    ";
        for (int c = 0; c < colonnes; c++) {
            if (couleur[l][c] != actuelle) {
                actuelle = couleur[l][c];
                cout << (actuelle == 1 ? FOND_ROUGE : actuelle == 2 ? FOND_NOIR : RESET);
            }
            cout << grille[l][c];
        }
        cout << RESET << "\n";
    }
}

// Tableau final : les noeuds niveau par niveau (parcours en largeur)
void afficherFin(Noeud* racine) {
    cout << "\nTABLEAU FINAL (niveau par niveau)\n";
    cout << "+--------+-------+---------+--------+--------+--------+\n";
    cout << "| Niveau | Noeud | Couleur | Parent | Gauche | Droite |\n";
    cout << "+--------+-------+---------+--------+--------+--------+\n";
    queue<pair<Noeud*, int>> file;
    file.push({racine, 0});
    while (!file.empty()) {
        Noeud* n = file.front().first;
        int niveau = file.front().second;
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
}

// ------------------------------------------------------------------------------
// Mesures
// ------------------------------------------------------------------------------

struct Resultat {
    string nom;
    size_t n;
    double insertion_ms, recherche_ms;
    int hauteur;
    size_t trouves;
};

// Remplit l'arbre avec les valeurs, puis les recherche toutes
Resultat mesurer(const string& nom, const vector<int>& valeurs, Noeud*& racine) {
    auto t0 = high_resolution_clock::now();
    for (int v : valeurs) inserer(racine, v);
    auto t1 = high_resolution_clock::now();

    size_t trouves = 0;
    for (int v : valeurs) trouves += rechercher(racine, v);
    auto t2 = high_resolution_clock::now();

    return {nom, valeurs.size(),
            duration<double, milli>(t1 - t0).count(),
            duration<double, milli>(t2 - t1).count(),
            hauteur(racine), trouves};
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

    // Cas 1 : 10 valeurs, on affiche les tableaux et l'arbre
    vector<int> dix = {1, 45, 67, 89, 12, 34, 23, 78, 56, 90};
    Noeud* arbre10 = nullptr;
    resultats.push_back(mesurer("10 valeurs", dix, arbre10));
    afficherDepart(dix);
    dessinerArbre(arbre10);
    afficherFin(arbre10);

    // Cas 2 et 3 : 1 000 et 100 000 valeurs melangees
    Noeud* arbre1000 = nullptr;
    Noeud* arbre100000 = nullptr;
    resultats.push_back(mesurer("1 000 valeurs", valeursMelangees(1000), arbre1000));
    resultats.push_back(mesurer("100 000 valeurs", valeursMelangees(100000), arbre100000));

    // Tableau des temps
    cout << "\nTEMPS ET HAUTEUR\n";
    string ligne = "+-----------------+---------+----------------+----------------+---------+-------------+---------+";
    cout << ligne << "\n";
    cout << "| Cas             |       n | Insertion (ms) | Recherche (ms) | Hauteur | 2*log2(n+1) | Trouves |\n";
    cout << ligne << "\n";
    for (const Resultat& r : resultats) {
        cout << "| " << left << setw(15) << r.nom << " | " << right
             << setw(7) << r.n << " | "
             << fixed << setprecision(4) << setw(14) << r.insertion_ms << " | "
             << setw(14) << r.recherche_ms << " | "
             << setw(7) << r.hauteur << " | "
             << setprecision(1) << setw(11) << 2 * log2(r.n + 1.0) << " | "
             << setw(7) << r.trouves << " |\n";
    }
    cout << ligne << "\n";
    cout << "La hauteur reste toujours sous 2*log2(n+1) : l'arbre reste equilibre.\n";

    liberer(arbre10);
    liberer(arbre1000);
    liberer(arbre100000);
    return 0;
}
