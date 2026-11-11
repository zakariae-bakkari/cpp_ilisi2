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
// Le nouveau noeud est ROUGE. Tant que son parent est rouge, on regarde l'oncle :
//   oncle rouge         -> recoloration, puis on remonte au grand-pere
//   oncle noir, zig-zag -> rotation au parent pour avoir une ligne
//   oncle noir, ligne   -> rotation au grand-pere + echange des couleurs

const string ROUGE = "\033[41;97;1m", NOIR = "\033[100;97;1m", RESET = "\033[0m";

struct Noeud {
    int cle;
    bool rouge;                       // true = rouge, false = noir
    Noeud *gauche, *droite, *parent;  // nullptr = feuille nil (noire)
};

bool estRouge(Noeud* n) { return n != nullptr && n->rouge; }  // nil = noir

// y prend la place de x chez le parent de x (ou devient la racine)
void remplacer(Noeud*& racine, Noeud* x, Noeud* y) {
    y->parent = x->parent;
    if (x->parent == nullptr) racine = y;
    else if (x == x->parent->gauche) x->parent->gauche = y;
    else x->parent->droite = y;
    x->parent = y;
}

void rotationGauche(Noeud*& racine, Noeud* x) {  // x descend a gauche
    Noeud* y = x->droite;
    x->droite = y->gauche;
    if (y->gauche) y->gauche->parent = x;
    remplacer(racine, x, y);
    y->gauche = x;
}

void rotationDroite(Noeud*& racine, Noeud* x) {  // x descend a droite
    Noeud* y = x->gauche;
    x->gauche = y->droite;
    if (y->droite) y->droite->parent = x;
    remplacer(racine, x, y);
    y->droite = x;
}

void reparer(Noeud*& racine, Noeud* n) {
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
    reparer(racine, n);
}

bool rechercher(Noeud* n, int cle) {
    while (n != nullptr && n->cle != cle) n = (cle < n->cle) ? n->gauche : n->droite;
    return n != nullptr;
}

int hauteur(Noeud* n) { return n ? 1 + max(hauteur(n->gauche), hauteur(n->droite)) : 0; }

void liberer(Noeud* n) {
    if (n == nullptr) return;
    liberer(n->gauche);
    liberer(n->droite);
    delete n;
}

// ------------------------------------------------------------------------------
// Affichage
// ------------------------------------------------------------------------------

void caseCouleur(int cle, bool rouge, int largeur = 5) {
    cout << (rouge ? ROUGE : NOIR) << setw(largeur) << cle << " " << RESET << "|";
}

string texte(Noeud* n) { return n ? to_string(n->cle) : "nil"; }

// Dessin : chaque noeud est une case de 4 colonnes, placee selon son rang
// dans l'ordre croissant. Ligne 2*prof : les noeuds, ligne suivante : / et \.
// couleur : 0 = rien, 1 = rouge, 2 = noir. Renvoie la colonne du noeud.
int placer(Noeud* n, int prof, int& rang, vector<string>& grille, vector<vector<int>>& couleur) {
    if (n == nullptr) return -1;
    int colG = placer(n->gauche, prof + 1, rang, grille, couleur);
    int col = 4 * rang++;
    int colD = placer(n->droite, prof + 1, rang, grille, couleur);

    int l = 2 * prof;
    string s = to_string(n->cle);
    for (int k = 0; k < 4; k++) couleur[l][col + k] = n->rouge ? 1 : 2;
    grille[l].replace(col + (4 - s.size()) / 2, s.size(), s);
    if (colG >= 0) {                                        // branche gauche
        grille[l + 1][colG + 2] = '/';
        for (int c = colG + 3; c < col; c++) grille[l][c] = '_';
    }
    if (colD >= 0) {                                        // branche droite
        grille[l + 1][colD + 1] = '\\';
        for (int c = col + 4; c < colD + 1; c++) grille[l][c] = '_';
    }
    return col;
}

void dessinerArbre(Noeud* racine, int nbNoeuds) {
    cout << "\nARBRE FINAL (rouge = noeud rouge, gris = noeud noir)\n\n";
    int lignes = 2 * hauteur(racine) - 1, colonnes = 4 * nbNoeuds, rang = 0;
    vector<string> grille(lignes, string(colonnes, ' '));
    vector<vector<int>> couleur(lignes, vector<int>(colonnes, 0));
    placer(racine, 0, rang, grille, couleur);
    for (int l = 0; l < lignes; l++) {
        cout << "    ";
        for (int c = 0; c < colonnes; c++) {
            if (c == 0 || couleur[l][c] != couleur[l][c - 1])
                cout << (couleur[l][c] == 1 ? ROUGE : couleur[l][c] == 2 ? NOIR : RESET);
            cout << grille[l][c];
        }
        cout << RESET << "\n";
    }
}

void afficherTableauFinal(Noeud* racine) {                 // parcours en largeur
    string sep = "+--------+-------+---------+--------+--------+--------+\n";
    cout << "\nTABLEAU FINAL (niveau par niveau)\n" << sep
         << "| Niveau | Noeud | Couleur | Parent | Gauche | Droite |\n" << sep;
    queue<pair<Noeud*, int>> file;
    file.push({racine, 0});
    while (!file.empty()) {
        auto [n, niveau] = file.front();
        file.pop();
        cout << "| " << setw(6) << niveau << " |";
        caseCouleur(n->cle, n->rouge, 6);
        cout << " " << left << setw(7) << (n->rouge ? "rouge" : "noir") << " | "
             << setw(6) << texte(n->parent) << " | " << setw(6) << texte(n->gauche) << " | "
             << setw(6) << texte(n->droite) << " |" << right << "\n";
        if (n->gauche) file.push({n->gauche, niveau + 1});
        if (n->droite) file.push({n->droite, niveau + 1});
    }
    cout << sep;
}

// Remplit l'arbre, recherche toutes les valeurs, puis affiche une ligne du tableau
void mesurer(const string& nom, const vector<int>& valeurs, Noeud*& racine) {
    auto t0 = high_resolution_clock::now();
    for (int v : valeurs) inserer(racine, v);
    auto t1 = high_resolution_clock::now();
    size_t trouves = 0;
    for (int v : valeurs) trouves += rechercher(racine, v);
    auto t2 = high_resolution_clock::now();

    size_t n = valeurs.size();
    cout << "| " << left << setw(15) << nom << " | " << right << setw(7) << n << " | "
         << fixed << setprecision(4) << setw(14) << duration<double, milli>(t1 - t0).count()
         << " | " << setw(14) << duration<double, milli>(t2 - t1).count() << " | "
         << setw(7) << hauteur(racine) << " | " << setprecision(1) << setw(11)
         << 2 * log2(n + 1.0) << " | " << setw(7) << trouves << " |\n";
}

int main() {
    // Cas 1 : 10 valeurs, avec les tableaux et le dessin
    vector<int> dix = {1, 45, 67, 89, 12, 34, 23, 78, 56, 90};
    cout << "\nTABLEAU DE DEPART (ordre d'insertion, chaque nouveau noeud est rouge)\n|";
    for (int v : dix) caseCouleur(v, true);
    cout << "\n";

    Noeud* arbre10 = nullptr;
    for (int v : dix) inserer(arbre10, v);
    dessinerArbre(arbre10, dix.size());
    afficherTableauFinal(arbre10);
    liberer(arbre10);

    // Temps pour 10, 1 000 et 100 000 valeurs (1..n melangees pour les deux derniers)
    string sep = "+-----------------+---------+----------------+----------------+---------+-------------+---------+\n";
    cout << "\nTEMPS ET HAUTEUR\n" << sep
         << "| Cas             |       n | Insertion (ms) | Recherche (ms) | Hauteur | 2*log2(n+1) | Trouves |\n" << sep;
    for (int n : {10, 1000, 100000}) {
        vector<int> valeurs = dix;
        if (n != 10) {
            valeurs.resize(n);
            for (int i = 0; i < n; i++) valeurs[i] = i + 1;
            shuffle(valeurs.begin(), valeurs.end(), mt19937(2026));
        }
        Noeud* racine = nullptr;
        mesurer(to_string(n) + " valeurs", valeurs, racine);
        liberer(racine);
    }
    cout << sep << "La hauteur reste toujours sous 2*log2(n+1) : l'arbre reste equilibre.\n";
    return 0;
}
