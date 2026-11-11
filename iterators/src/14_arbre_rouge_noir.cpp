#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <cmath>
#include <cstdlib>

using namespace std;

// ==============================================================================
// ARBRE ROUGE-NOIR : INSERTION, REPARATION, VERIFICATION ET AFFICHAGE
// ==============================================================================
//
// Les 5 regles :
//   1) chaque noeud est rouge ou noir
//   2) la racine est noire
//   3) les feuilles nil sont noires        (ici nil = nullptr)
//   4) un noeud rouge n'a pas d'enfant rouge
//   5) meme nombre de noirs sur tous les chemins d'un noeud jusqu'aux nil
//
// Insertion : on insere comme dans un ABR, le nouveau noeud N est ROUGE, puis
// tant que son parent P est rouge on repare en regardant l'oncle U :
//   cas A : U rouge          -> recoloration, puis on recommence avec G
//   cas B : U noir, ligne    -> rotation en G, echange des couleurs de P et G
//   cas C : U noir, zig-zag  -> rotation en P pour avoir une ligne, puis cas B

enum Couleur { ROUGE, NOIR };

struct Noeud {
    int cle;
    Couleur couleur;
    Noeud* gauche = nullptr;  // nullptr = feuille nil (noire)
    Noeud* droite = nullptr;
    Noeud* parent = nullptr;
    Noeud(int c, Couleur col, Noeud* p) : cle(c), couleur(col), parent(p) {}
};

// Un nil (nullptr) compte comme NOIR : c'est la regle 3.
// Piege : sans cette fonction, u->couleur plante quand l'oncle est nil.
bool estRouge(Noeud* n) { return n != nullptr && n->couleur == ROUGE; }

string nom(Noeud* n) {
    if (n == nullptr) return "nil";
    return to_string(n->cle) + (n->couleur == ROUGE ? "(R)" : "(N)");
}

class ArbreRN {
public:
    Noeud* racine = nullptr;
    bool bavard;
    int casA = 0, casB = 0, casC = 0;  // nombre de fois ou chaque cas est utilise

    explicit ArbreRN(bool b = false) : bavard(b) {}
    ~ArbreRN() { liberer(racine); }

    // ------------------------------------------------------------------
    // Rotations
    // ------------------------------------------------------------------

    /*        x                     y
             / \                   / \
            A   y      ==>        x   C
               / \               / \
              B   C             A   B          */
    void rotationGauche(Noeud* x) {
        Noeud* y = x->droite;
        // 1) le sous-arbre B passe de y a x
        x->droite = y->gauche;
        if (y->gauche != nullptr) y->gauche->parent = x;
        // 2) y prend la place de x chez le parent de x
        y->parent = x->parent;
        if (x->parent == nullptr) racine = y;  // piege : mettre a jour la racine
        else if (x == x->parent->gauche) x->parent->gauche = y;
        else x->parent->droite = y;
        // 3) x devient le fils gauche de y
        y->gauche = x;
        x->parent = y;
    }

    // Miroir exact de rotationGauche.
    void rotationDroite(Noeud* x) {
        Noeud* y = x->gauche;
        x->gauche = y->droite;
        if (y->droite != nullptr) y->droite->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) racine = y;
        else if (x == x->parent->droite) x->parent->droite = y;
        else x->parent->gauche = y;
        y->droite = x;
        x->parent = y;
    }

    // ------------------------------------------------------------------
    // Insertion
    // ------------------------------------------------------------------
    bool inserer(int cle) {
        // Etape a) descente comme dans un arbre binaire de recherche
        Noeud* parent = nullptr;
        Noeud* courant = racine;
        string chemin;
        while (courant != nullptr) {
            chemin += (chemin.empty() ? "" : " -> ") + to_string(courant->cle);
            parent = courant;
            if (cle < courant->cle) courant = courant->gauche;
            else if (cle > courant->cle) courant = courant->droite;
            else {
                if (bavard) cout << cle << " est deja present : rien a faire.\n";
                return false;
            }
        }

        // Etape b) le nouveau noeud est ROUGE : la hauteur noire ne change pas,
        // donc la regle 5 reste vraie. Seule la regle 4 (ou 2) peut casser.
        Noeud* n = new Noeud(cle, ROUGE, parent);
        string place;
        if (parent == nullptr) {
            racine = n;
            place = "arbre vide : N devient la racine";
        } else if (cle < parent->cle) {
            parent->gauche = n;
            place = "a gauche de " + to_string(parent->cle);
        } else {
            parent->droite = n;
            place = "a droite de " + to_string(parent->cle);
        }

        if (bavard) {
            cout << "=== Insertion de " << cle << " ===\n";
            cout << "Chemin : " << (chemin.empty() ? "(aucun)" : chemin)
                 << " ; N place " << place << "\n";
            cout << "Arbre AVANT reparation :\n";
            afficher();
        }

        // Etapes c) et d)
        reparer(n);

        if (bavard) {
            cout << "Arbre APRES reparation :\n";
            afficher();
            cout << "\n";
        }
        return true;
    }

    void reparer(Noeud* n) {
        if (bavard && n->parent != nullptr && !estRouge(n->parent))
            cout << "Parent P=" << nom(n->parent) << " noir : rien a reparer.\n";

        // Etape c) tant que le parent est rouge, on a un rouge-rouge (regle 4)
        while (estRouge(n->parent)) {
            Noeud* p = n->parent;
            Noeud* g = p->parent;  // existe : P rouge n'est jamais la racine
            bool pAGauche = (p == g->gauche);
            Noeud* u = pAGauche ? g->droite : g->gauche;  // cas miroir gere ici
            string coteP = pAGauche ? "gauche" : "droite";

            if (bavard)
                cout << "N=" << nom(n) << ", P=" << nom(p) << " rouge, G=" << nom(g)
                     << ", U=" << nom(u) << "\n";

            // ---- Cas A : oncle rouge -> recoloration ----
            // On descend le noir de G vers P et U : chaque chemin passant par G
            // garde le meme nombre de noirs. Mais G devient rouge : il peut
            // former un rouge-rouge avec son parent, donc on REBOUCLE sur G.
            if (estRouge(u)) {
                casA++;
                p->couleur = NOIR;
                u->couleur = NOIR;
                g->couleur = ROUGE;
                if (bavard)
                    cout << "  Cas A (oncle rouge) : " << p->cle << " et " << u->cle
                         << " en noir, " << g->cle << " en rouge ; on recommence avec N="
                         << g->cle << "\n";
                n = g;  // piege : ne pas oublier de reboucler
                continue;
            }

            // Oncle noir ou nil : recolorer seul enleverait un noir aux chemins
            // passant par U (regle 5). Il faut changer la forme : rotation.
            bool nAGauche = (n == p->gauche);

            // ---- Cas C : zig-zag -> rotation en P pour obtenir une ligne ----
            // Piege : tourner directement en G laisserait N sous un noeud rouge.
            if (nAGauche != pAGauche) {
                casC++;
                if (bavard)
                    cout << "  Cas C (oncle noir, zig-zag " << coteP << "-"
                         << (nAGauche ? "gauche" : "droite") << ") : rotation "
                         << (pAGauche ? "gauche" : "droite") << " en " << p->cle << "\n";
                if (pAGauche) rotationGauche(p);
                else rotationDroite(p);
                swap(n, p);  // l'ancien N est maintenant le parent
            }

            // ---- Cas B : ligne -> rotation en G + echange des couleurs ----
            // P monte a la place de G et devient noir, N et G sont ses enfants
            // rouges : le nombre de noirs par chemin ne change pas.
            casB++;
            if (pAGauche) rotationDroite(g);
            else rotationGauche(g);
            swap(p->couleur, g->couleur);
            if (bavard)
                cout << "  Cas B (oncle noir, ligne " << coteP << "-" << coteP
                     << ") : rotation " << (pAGauche ? "droite" : "gauche") << " en "
                     << g->cle << ", " << p->cle << " devient noir et " << g->cle
                     << " rouge\n";
            // P est noir : la boucle s'arrete
        }

        // Regle 2 : la racine est toujours remise en noir
        if (racine->couleur == ROUGE) {
            if (bavard)
                cout << "Racine " << racine->cle << " rouge -> remise en noir (regle 2)\n";
            racine->couleur = NOIR;
        }
    }

    // ------------------------------------------------------------------
    // Verification : renvoie la liste des regles violees (vide = correct)
    // ------------------------------------------------------------------
    vector<string> verifier() const {
        vector<string> erreurs;
        if (racine == nullptr) return erreurs;
        if (racine->couleur != NOIR)
            erreurs.push_back("Regle 2 : la racine " + to_string(racine->cle) + " est rouge");
        if (racine->parent != nullptr)
            erreurs.push_back("Lien parent : la racine a un parent");
        verifierRec(racine, nullptr, nullptr, erreurs);
        return erreurs;
    }

    // ------------------------------------------------------------------
    // Outils
    // ------------------------------------------------------------------
    int hauteur() const { return hauteurRec(racine); }

    void parcoursInfixe(Noeud* n, vector<int>& res) const {
        if (n == nullptr) return;
        parcoursInfixe(n->gauche, res);
        res.push_back(n->cle);
        parcoursInfixe(n->droite, res);
    }

    // Affiche chaque chemin racine -> nil avec son nombre de noirs (sans le nil).
    void afficherCheminsVersNil() const {
        vector<string> chemin;
        cheminsRec(racine, chemin, 0);
    }

    // Affiche l'arbre couche : g = fils gauche, d = fils droit.
    void afficher(bool nils = false) const {
        if (racine == nullptr) { cout << "(arbre vide)\n"; return; }
        cout << nom(racine) << "\n";
        afficherRec(racine, "", nils);
    }

private:
    // Renvoie la hauteur noire de n (un nil compte pour 1).
    int verifierRec(Noeud* n, const int* mini, const int* maxi,
                    vector<string>& erreurs) const {
        if (n == nullptr) return 1;
        string c = to_string(n->cle);
        if (n->couleur != ROUGE && n->couleur != NOIR)
            erreurs.push_back("Regle 1 : " + c + " n'est ni rouge ni noir");
        if ((mini && n->cle <= *mini) || (maxi && n->cle >= *maxi))
            erreurs.push_back("Ordre ABR : " + c + " est mal place");
        for (Noeud* e : {n->gauche, n->droite}) {
            if (e != nullptr && e->parent != n)
                erreurs.push_back("Lien parent : " + to_string(e->cle) +
                                  " ne pointe pas vers " + c);
            if (n->couleur == ROUGE && estRouge(e))
                erreurs.push_back("Regle 4 : rouge-rouge entre " + c + " et " +
                                  to_string(e->cle));
        }
        int hg = verifierRec(n->gauche, mini, &n->cle, erreurs);
        int hd = verifierRec(n->droite, &n->cle, maxi, erreurs);
        if (hg != hd)
            erreurs.push_back("Regle 5 : sous " + c + ", hauteur noire " + to_string(hg) +
                              " a gauche et " + to_string(hd) + " a droite");
        return max(hg, hd) + (n->couleur == NOIR ? 1 : 0);
    }

    int hauteurRec(Noeud* n) const {
        if (n == nullptr) return 0;
        return 1 + max(hauteurRec(n->gauche), hauteurRec(n->droite));
    }

    void cheminsRec(Noeud* n, vector<string>& chemin, int noirs) const {
        if (n == nullptr) {
            string s;
            for (const string& x : chemin) s += x + " -> ";
            s += "nil";
            cout << "  " << s << string(s.size() < 40 ? 40 - s.size() : 1, ' ')
                 << "noirs = " << noirs << "\n";
            return;
        }
        noirs += (n->couleur == NOIR ? 1 : 0);
        chemin.push_back(nom(n));
        cheminsRec(n->gauche, chemin, noirs);
        cheminsRec(n->droite, chemin, noirs);
        chemin.pop_back();
    }

    void afficherRec(Noeud* n, const string& prefixe, bool nils) const {
        if (!nils && n->gauche == nullptr && n->droite == nullptr) return;
        cout << prefixe << "|-- g: " << nom(n->gauche) << "\n";
        if (n->gauche) afficherRec(n->gauche, prefixe + "|   ", nils);
        cout << prefixe << "`-- d: " << nom(n->droite) << "\n";
        if (n->droite) afficherRec(n->droite, prefixe + "    ", nils);
    }

    void liberer(Noeud* n) {
        if (n == nullptr) return;
        liberer(n->gauche);
        liberer(n->droite);
        delete n;
    }
};

// ==============================================================================
// Tests
// ==============================================================================

void afficherErreurs(const vector<string>& erreurs) {
    if (erreurs.empty()) { cout << "aucune regle violee\n"; return; }
    for (size_t i = 0; i < erreurs.size(); i++)
        cout << (i ? "                                     " : "") << "[" << erreurs[i] << "]\n";
}

void verifierOuQuitter(const ArbreRN& a) {
    vector<string> e = a.verifier();
    if (!e.empty()) {
        cout << "ERREUR : ";
        afficherErreurs(e);
        exit(1);
    }
}

const vector<int> EXEMPLE = {41, 38, 31, 12, 19, 8, 50, 55};

void testExemple() {
    cout << string(60, '#') << "\n# TEST 1 : exemple 41, 38, 31, 12, 19, 8, 50, 55\n"
         << string(60, '#') << "\n";
    ArbreRN a(true);
    for (int c : EXEMPLE) a.inserer(c);
    cout << "Arbre final avec les feuilles nil :\n";
    a.afficher(true);
    cout << "\nChemins racine -> nil (noirs comptes sans le nil) :\n";
    a.afficherCheminsVersNil();
    cout << "verifier() : ";
    afficherErreurs(a.verifier());
    cout << "Cas utilises : A=" << a.casA << " B=" << a.casB << " C=" << a.casC
         << " | hauteur : " << a.hauteur() << "\n\n";
}

void testAleatoire() {
    cout << string(60, '#') << "\n# TEST 2 : suites aleatoires (verifier() apres chaque insertion)\n"
         << string(60, '#') << "\n";
    mt19937 gen(2026);
    const int nbSuites = 300;
    long nbInsertions = 0;
    vector<int> pool(10000);
    for (int i = 0; i < 10000; i++) pool[i] = i;
    for (int s = 0; s < nbSuites; s++) {
        shuffle(pool.begin(), pool.end(), gen);
        int taille = uniform_int_distribution<int>(1, 300)(gen);
        vector<int> cles(pool.begin(), pool.begin() + taille);  // cles distinctes
        ArbreRN a;
        for (int c : cles) {
            a.inserer(c);
            nbInsertions++;
            verifierOuQuitter(a);
        }
        vector<int> infixe;
        a.parcoursInfixe(a.racine, infixe);
        sort(cles.begin(), cles.end());
        if (infixe != cles || a.hauteur() > 2 * log2(taille + 1.0)) {
            cout << "ERREUR : ordre ou hauteur incorrects\n";
            exit(1);
        }
    }
    cout << nbSuites << " suites, " << nbInsertions << " insertions : aucune regle violee\n\n";
}

void testTrie() {
    cout << string(60, '#') << "\n# TEST 3 : suite triee de 1 a 2000\n" << string(60, '#') << "\n";
    ArbreRN a;
    for (int c = 1; c <= 2000; c++) {
        a.inserer(c);
        verifierOuQuitter(a);
    }
    cout << "verifier() : ";
    afficherErreurs(a.verifier());
    cout << "Hauteur = " << a.hauteur() << " (ABR naif : 2000 ; borne 2*log2(n+1) = "
         << round(2 * log2(2001.0) * 10) / 10 << ")\n";
    cout << "Racine = " << nom(a.racine) << " ; cas utilises : A=" << a.casA
         << " B=" << a.casB << " C=" << a.casC << "\n\n";
}

void testDetection() {
    cout << string(60, '#') << "\n# TEST 4 : verifier() detecte les arbres faux\n"
         << string(60, '#') << "\n";

    // Regle 2 : arbre 20(N) [10(N) [5(R)], 30(N)] puis racine peinte en rouge
    {
        ArbreRN a;
        for (int c : {20, 10, 30, 5}) a.inserer(c);
        a.racine->couleur = ROUGE;
        cout << "Racine 20 peinte en rouge          -> ";
        afficherErreurs(a.verifier());
    }
    // Regle 4 : on accroche 45 rouge sous 41 rouge, SANS reparer
    {
        ArbreRN a;
        for (int c : EXEMPLE) a.inserer(c);
        Noeud* n41 = a.racine->droite->gauche;
        n41->droite = new Noeud(45, ROUGE, n41);
        cout << "45 rouge accroche sous 41 rouge    -> ";
        afficherErreurs(a.verifier());
    }
    // Regle 5 : 41 peint en noir -> un noir de trop sur ses chemins
    {
        ArbreRN a;
        for (int c : EXEMPLE) a.inserer(c);
        a.racine->droite->gauche->couleur = NOIR;
        cout << "Noeud 41 peint en noir             -> ";
        afficherErreurs(a.verifier());
    }
    cout << "\n";
}

int main() {
    testExemple();
    testAleatoire();
    testTrie();
    testDetection();
    return 0;
}
