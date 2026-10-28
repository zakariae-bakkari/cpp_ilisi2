#include <iostream>
#include <iomanip>     // Pour un affichage sous forme de tableau propre
#include <string>
#include <queue>       // Hauteur calculée niveau par niveau (comme le BFS)
#include <chrono>      // Mesure du temps en millisecondes
#include <functional>
#include <map>         // std::map : arbre rouge-noir (ABR auto-équilibré) de la STL
#include <cmath>       // log2()
#include <csignal>     // SIGALRM / SIGSEGV
#include <unistd.h>    // fork(), alarm(), _exit()
#include <sys/wait.h>  // waitpid()
#include <sys/resource.h> // getrlimit() : taille de la pile

using namespace std;

// ==============================================================================
// STRUCTURE DE NŒUD D'ARBRE BINAIRE DE RECHERCHE (ABR)
// ==============================================================================
// Règle d'or : pour chaque nœud,
//   - toutes les valeurs du sous-arbre GAUCHE sont plus PETITES
//   - toutes les valeurs du sous-arbre DROIT sont plus GRANDES
struct Noeud {
    int valeur;
    Noeud* gauche;
    Noeud* droite;

    Noeud(int val) : valeur(val), gauche(nullptr), droite(nullptr) {}
};

// ==============================================================================
// 1. INSERTION
// ==============================================================================

/**
 * @brief Insère une valeur dans l'ABR en respectant la règle d'ordre.
 * On descend à gauche si la valeur est plus petite, à droite si elle est plus
 * grande, jusqu'à trouver une place vide (nullptr) où créer le nouveau nœud.
 * Les doublons sont ignorés.
 *
 * @param racine Pointeur vers la racine (peut être nullptr si l'arbre est vide)
 * @param val    Valeur à insérer
 * @return La racine de l'arbre (nouvelle racine si l'arbre était vide)
 */
Noeud* inserer(Noeud* racine, int val) {
    if (!racine) return new Noeud(val);   // place vide trouvée

    if (val < racine->valeur) {
        racine->gauche = inserer(racine->gauche, val);
    } else if (val > racine->valeur) {
        racine->droite = inserer(racine->droite, val);
    }
    // val == racine->valeur : doublon, on ne fait rien
    return racine;
}

// ==============================================================================
// 2. RECHERCHE
// ==============================================================================

/**
 * @brief Recherche une valeur dans l'ABR (version itérative).
 * À chaque nœud on élimine tout un sous-arbre : O(h) comparaisons,
 * avec h la hauteur de l'arbre (O(log n) si l'arbre est équilibré).
 *
 * @return Le nœud trouvé, ou nullptr si la valeur est absente
 */
Noeud* rechercher(Noeud* racine, int val) {
    Noeud* courant = racine;
    while (courant) {
        if (val == courant->valeur) return courant;
        courant = (val < courant->valeur) ? courant->gauche : courant->droite;
    }
    return nullptr;
}

// ==============================================================================
// FONCTION DE VISUALISATION : TRACÉ DE LA RECHERCHE ÉTAPE PAR ÉTAPE
// ==============================================================================

/**
 * @brief Même algorithme que rechercher(), mais affiche chaque comparaison
 * sous forme de tableau (fonction séparée pour ne pas encombrer rechercher()).
 */
void tracerRecherche(Noeud* racine, int val) {
    cout << "\n Recherche de " << val << " :\n";
    cout << "| " << left << setw(8)  << "Etape"
         << "| " << left << setw(8)  << "Noeud"
         << "| " << left << setw(14) << "Comparaison"
         << "| " << left << setw(18) << "Decision" << " |\n";
    cout << "|---------|---------|---------------|--------------------|\n";

    Noeud* courant = racine;
    int etape = 1;
    while (courant) {
        string comparaison, decision;
        if (val == courant->valeur) {
            comparaison = to_string(val) + " == " + to_string(courant->valeur);
            decision = "TROUVE";
        } else if (val < courant->valeur) {
            comparaison = to_string(val) + " < " + to_string(courant->valeur);
            decision = "aller a gauche";
        } else {
            comparaison = to_string(val) + " > " + to_string(courant->valeur);
            decision = "aller a droite";
        }

        cout << "| " << left << setw(8)  << ("#" + to_string(etape++))
             << "| " << left << setw(8)  << courant->valeur
             << "| " << left << setw(14) << comparaison
             << "| " << left << setw(18) << decision << " |\n";

        if (val == courant->valeur) return;
        courant = (val < courant->valeur) ? courant->gauche : courant->droite;
    }
    cout << "| " << left << setw(8) << "-"
         << "| " << left << setw(8) << "nullptr"
         << "| " << left << setw(14) << "-"
         << "| " << left << setw(18) << "ABSENT" << " |\n";
}

/**
 * @brief Parcours infixe (gauche, racine, droite) : affiche les valeurs triées.
 * Sert à vérifier que l'insertion respecte bien la règle d'ordre.
 */
void afficherInfixe(Noeud* racine) {
    if (!racine) return;
    afficherInfixe(racine->gauche);
    cout << racine->valeur << " ";
    afficherInfixe(racine->droite);
}

/**
 * @brief Libère proprement la mémoire allouée dynamiquement pour l'arbre.
 */
void libererArbre(Noeud* racine) {
    if (!racine) return;
    libererArbre(racine->gauche);
    libererArbre(racine->droite);
    delete racine;
}

/**
 * @brief Hauteur de l'arbre (-1 pour un arbre vide, 0 pour un seul nœud).
 * Calculée niveau par niveau avec une file (même principe que le BFS du 07) :
 * pas de récursion, donc pas de stack overflow même sur une chaîne d'un million de nœuds.
 */
int hauteur(Noeud* racine) {
    if (!racine) return -1;
    queue<Noeud*> fileAttente;
    fileAttente.push(racine);
    int h = -1;
    while (!fileAttente.empty()) {
        size_t tailleNiveau = fileAttente.size();
        for (size_t i = 0; i < tailleNiveau; i++) {
            Noeud* courant = fileAttente.front();
            fileAttente.pop();
            if (courant->gauche) fileAttente.push(courant->gauche);
            if (courant->droite) fileAttente.push(courant->droite);
        }
        h++;   // un niveau de plus
    }
    return h;
}

// ==============================================================================
// EXPÉRIENCE : INSERTION DE VALEURS CROISSANTES (PIRE CAS)
// ==============================================================================
// Avec 1, 2, 3, ... chaque valeur est plus grande que toutes les autres : elle part
// toujours à droite. L'arbre devient une "liste chaînée" de hauteur n - 1 :
//   - la i-ème insertion fait i - 1 comparaisons -> n(n-1)/2 au total : O(n²)
//   - inserer() est récursive : une profondeur n = n appels empilés -> stack overflow

const int LIMITE_MS = 10000;  // au-delà, on considère le programme "bloqué"

/**
 * @brief Construit une chaîne 1 -> 2 -> ... -> n SANS récursion (rapide, sans risque pour la pile).
 */
Noeud* construireChaine(int n) {
    Noeud* racine = new Noeud(1);
    Noeud* dernier = racine;
    for (int i = 2; i <= n; i++) {
        dernier->droite = new Noeud(i);
        dernier = dernier->droite;
    }
    return racine;
}

/**
 * @brief Exécute une expérience dans un processus enfant (fork) pour qu'un plantage
 * (stack overflow) ou un dépassement de LIMITE_MS ne tue pas tout le programme.
 * La mémoire de l'enfant est rendue au système à sa fin (_exit).
 *
 * @return "OK", "BLOQUE : trop lent (> LIMITE_MS ms)" ou "BLOQUE : stack overflow (segfault)"
 */
string lancerDansEnfant(const function<void()>& experience) {
    cout.flush();
    pid_t pid = fork();
    if (pid == 0) {
        alarm((LIMITE_MS + 999) / 1000);  // SIGALRM tue l'enfant s'il dépasse la limite
        experience();
        cout.flush();
        _exit(0);
    }
    int statut = 0;
    waitpid(pid, &statut, 0);
    if (WIFSIGNALED(statut)) {
        if (WTERMSIG(statut) == SIGALRM) return "BLOQUE : trop lent (> " + to_string(LIMITE_MS) + " ms)";
        if (WTERMSIG(statut) == SIGSEGV) return "BLOQUE : stack overflow (segfault)";
        return "BLOQUE : signal " + to_string(WTERMSIG(statut));
    }
    return "OK";
}

double millisecondesDepuis(chrono::steady_clock::time_point debut) {
    return chrono::duration<double, milli>(chrono::steady_clock::now() - debut).count();
}

// ==============================================================================
// CAPACITÉ DE LA PILE
// ==============================================================================

/**
 * @brief Taille maximale de la pile du processus (équivalent de `ulimit -s`), en Ko.
 * @return -1 si la pile est illimitée
 */
long taillePileKo() {
    rlimit limite;
    getrlimit(RLIMIT_STACK, &limite);
    if (limite.rlim_cur == RLIM_INFINITY) return -1;
    return (long)(limite.rlim_cur / 1024);
}

/**
 * @brief Profondeur maximale que inserer() peut atteindre avant le stack overflow.
 * Recherche dichotomique entre une profondeur qui passe (bas) et une qui plante (haut) :
 * chaque essai tourne dans un processus enfant, le plantage ne tue donc pas le programme.
 */
int profondeurMaxPile(int bas, int haut, int precision) {
    while (haut - bas > precision) {
        int milieu = bas + (haut - bas) / 2;
        string etat = lancerDansEnfant([milieu] {
            Noeud* r = construireChaine(milieu);
            inserer(r, milieu + 1);
        });
        if (etat == "OK") bas = milieu; else haut = milieu;
    }
    return bas;
}

// ==============================================================================
// COMPARAISON AVEC std::map (ARBRE ROUGE-NOIR)
// ==============================================================================
// Schéma affiché en section 7 (chaîne brute R"(...)" : pas de "\" en fin de commentaire)
const char* SCHEMA_ABR_VS_MAP = R"(
   NOTRE ABR (inserer)                       std::map (arbre rouge-noir)
   insertion de 1, 2, ..., 10                insertion de 1, 2, ..., 10

   1                                                 4
   '-> 2                                           /   \
       '-> 3                                      2     6
           '-> 4                                 / \   / \
               '-> ...                          1   3 5   8(R)
                   '-> 10                            / \
                                                    7   9
   tout part a droite : une chaine                       '-> 10(R)
   hauteur 9                                 hauteur 4   (R) = noeud rouge

   - aucun reequilibrage                     - rotations + couleurs apres chaque insertion
   - hauteur h = n - 1                       - hauteur h <= 2 log2(n + 1)
   - insertion recursive : n appels empiles  - insertion iterative : pile constante
   - n insertions : O(n^2)                   - n insertions : O(n log n)
)";

/**
 * @brief Hauteur réelle de l'arbre rouge-noir caché dans un std::map.
 * Propre à libstdc++ (g++) : end()._M_node est le nœud "en-tête", dont _M_parent est la racine.
 * Calcul niveau par niveau, comme hauteur().
 */
int hauteurMap(const map<int, int>& m) {
    if (m.empty()) return -1;
    const _Rb_tree_node_base* racine = m.end()._M_node->_M_parent;
    queue<const _Rb_tree_node_base*> fileAttente;
    fileAttente.push(racine);
    int h = -1;
    while (!fileAttente.empty()) {
        size_t tailleNiveau = fileAttente.size();
        for (size_t i = 0; i < tailleNiveau; i++) {
            const _Rb_tree_node_base* courant = fileAttente.front();
            fileAttente.pop();
            if (courant->_M_left)  fileAttente.push(courant->_M_left);
            if (courant->_M_right) fileAttente.push(courant->_M_right);
        }
        h++;
    }
    return h;
}

// ==============================================================================
// MAIN DE TEST
// ==============================================================================
int main() {
    cout << "=================================================================" << endl;
    cout << " 1. INSERTION DE 1 JUSQU'A 10 (inserer)" << endl;
    cout << "=================================================================" << endl;
    cout << "| " << left << setw(10) << "insertion"
         << "| " << left << setw(8)  << "hauteur"
         << "| " << left << setw(12) << "temps (ms)"
         << "| " << left << setw(28) << "infixe (valeurs triees)" << " |\n";
    cout << "|-----------|---------|-------------|------------------------------|\n";

    Noeud* racine = nullptr;
    double totalMs = 0;
    for (int v = 1; v <= 10; v++) {
        auto t0 = chrono::steady_clock::now();
        racine = inserer(racine, v);
        double ms = millisecondesDepuis(t0);
        totalMs += ms;

        // infixe dans une chaîne pour l'aligner dans le tableau
        string infixe;
        for (int x = 1; x <= v; x++) infixe += to_string(x) + " ";

        cout << "| " << left << setw(10) << v
             << "| " << left << setw(8)  << hauteur(racine)
             << "| " << left << setw(12) << fixed << setprecision(4) << ms
             << "| " << left << setw(28) << infixe << " |\n";
    }
    cout << "\nTemps total : " << fixed << setprecision(4) << totalMs << " ms\n";
    cout << "Forme obtenue (chaque valeur est plus grande : tout part a droite) :\n  ";
    for (Noeud* n = racine; n; n = n->droite) cout << n->valeur << (n->droite ? " -> " : "\n");
    cout << "Hauteur finale : " << hauteur(racine)
         << " (au lieu de 3 pour un arbre equilibre de 10 noeuds)\n";
    cout << "(Le parcours infixe reste trie : la regle d'ordre est respectee)\n";
    cout << "Verification avec afficherInfixe : ";
    afficherInfixe(racine);
    cout << "\n\n";

    cout << "=================================================================" << endl;
    cout << " 2. RECHERCHE (rechercher) :" << endl;
    cout << "=================================================================" << endl;
    int cibles[] = {10, 15};
    for (int c : cibles) {
        cout << "rechercher(" << c << ") : "
             << (rechercher(racine, c) ? "trouve" : "absent") << endl;
    }

    cout << "\n=================================================================" << endl;
    cout << " 3. TRACE ETAPE PAR ETAPE (tracerRecherche) :" << endl;
    cout << "    (10 comparaisons pour trouver 10 : comme dans une liste)" << endl;
    cout << "=================================================================" << endl;
    for (int c : cibles) tracerRecherche(racine, c);
    cout << endl;

    libererArbre(racine);

    cout << "\n=================================================================" << endl;
    cout << " 4. MILLIERS DE VALEURS CROISSANTES : QUAND EST-CE QUE CA BLOQUE ?" << endl;
    cout << "    (limite fixee a " << LIMITE_MS << " ms)" << endl;
    cout << "=================================================================" << endl;
    cout << "| " << left << setw(10) << "n"
         << "| " << left << setw(10) << "hauteur"
         << "| " << left << setw(16) << "comparaisons"
         << "| " << left << setw(14) << "temps (ms)"
         << "| " << left << setw(40) << "etat" << " |\n";
    cout << "|-----------|-----------|-----------------|---------------|------------------------------------------|\n";

    int tailles[] = {1000, 2000, 5000, 10000, 20000, 30000, 50000, 100000};
    for (int n : tailles) {
        long long comparaisons = (long long)n * (n - 1) / 2;
        cout << "| " << left << setw(10) << n << "| ";
        string etat = lancerDansEnfant([n, comparaisons] {
            Noeud* r = nullptr;
            auto t0 = chrono::steady_clock::now();
            for (int v = 1; v <= n; v++) r = inserer(r, v);
            double ms = millisecondesDepuis(t0);   // la hauteur n'est pas comptée dans le temps
            cout << left << setw(10) << hauteur(r) << "| "
                 << left << setw(16) << comparaisons << "| "
                 << left << setw(14) << fixed << setprecision(1) << ms << "| ";
        });
        if (etat != "OK") {
            cout << left << setw(10) << "-" << "| "
                 << left << setw(16) << comparaisons << "| "
                 << left << setw(14) << "-" << "| ";
        }
        cout << left << setw(40) << etat << " |" << endl;
        if (etat != "OK") break;   // inutile d'essayer plus grand
    }

    cout << "\n=================================================================" << endl;
    cout << " 5. LIMITE DE LA PILE : UNE SEULE insertion recursive au bout d'une chaine" << endl;
    cout << "    (chaine construite sans recursion pour ne mesurer que la pile)" << endl;
    cout << "=================================================================" << endl;
    cout << "| " << left << setw(12) << "profondeur"
         << "| " << left << setw(10) << "hauteur"
         << "| " << left << setw(14) << "temps (ms)"
         << "| " << left << setw(40) << "etat" << " |\n";
    cout << "|-------------|-----------|---------------|------------------------------------------|\n";

    int profondeurs[] = {100000, 200000, 500000, 1000000, 2000000, 5000000};
    for (int n : profondeurs) {
        cout << "| " << left << setw(12) << n << "| ";
        string etat = lancerDansEnfant([n] {
            Noeud* r = construireChaine(n);
            auto t0 = chrono::steady_clock::now();
            inserer(r, n + 1);   // n appels récursifs empilés
            double ms = millisecondesDepuis(t0);
            cout << left << setw(10) << hauteur(r) << "| "
                 << left << setw(14) << fixed << setprecision(1) << ms << "| ";
        });
        if (etat != "OK") cout << left << setw(10) << "-" << "| " << left << setw(14) << "-" << "| ";
        cout << left << setw(40) << etat << " |" << endl;
        if (etat != "OK") break;
    }
    cout << "\n=================================================================" << endl;
    cout << " 6. CAPACITE DE LA PILE DE CETTE MACHINE" << endl;
    cout << "=================================================================" << endl;
    long pileKo = taillePileKo();
    if (pileKo < 0) {
        cout << "Pile illimitee (ulimit -s unlimited) : pas de mesure possible.\n";
    } else {
        int maxProfondeur = profondeurMaxPile(100000, 20000000, 1000);
        cout << "Taille de la pile (ulimit -s)       : " << pileKo << " Ko\n";
        cout << "Profondeur max de inserer() (+-1000) : " << maxProfondeur << " appels\n";
        cout << "Place occupee par un appel           : ~" << fixed << setprecision(1)
             << pileKo * 1024.0 / maxProfondeur << " octets\n";
        cout << "(Le seuil depend aussi de -O0/-O3 : sans optimisation chaque appel prend plus de place.)\n";
    }

    cout << "\n=================================================================" << endl;
    cout << " 7. COMPARAISON NOTRE ABR / std::map (valeurs croissantes 1..n)" << endl;
    cout << "    (std::map = arbre rouge-noir : il se reequilibre apres chaque insertion)" << endl;
    cout << "=================================================================" << endl;
    cout << SCHEMA_ABR_VS_MAP << endl;
    cout << "| " << left << setw(9)  << "n"
         << "| " << left << setw(9)  << "h ABR"
         << "| " << left << setw(15) << "temps ABR (ms)"
         << "| " << left << setw(7)  << "h map"
         << "| " << left << setw(12) << "2log2(n+1)"
         << "| " << left << setw(15) << "temps map (ms)" << " |\n";
    cout << "|----------|----------|----------------|--------|-------------|-----------------|\n";

    int taillesMap[] = {10, 1000, 10000, 30000, 50000, 1000000};
    for (int n : taillesMap) {
        cout << "| " << left << setw(9) << n << "| ";
        // Au-delà de 30 000 l'ABR dépasse la limite (section 4) : inutile d'attendre 10 s de plus
        string etat = "BLOQUE";
        if (n <= 30000) {
            etat = lancerDansEnfant([n] {
                Noeud* r = nullptr;
                auto t0 = chrono::steady_clock::now();
                for (int v = 1; v <= n; v++) r = inserer(r, v);
                double ms = millisecondesDepuis(t0);
                cout << left << setw(9) << hauteur(r) << "| "
                     << left << setw(15) << fixed << setprecision(2) << ms << "| ";
            });
        }
        if (etat != "OK") cout << left << setw(9) << "-" << "| " << left << setw(15) << "bloque" << "| ";

        map<int, int> m;
        auto t0 = chrono::steady_clock::now();
        for (int v = 1; v <= n; v++) m[v] = v;
        double ms = millisecondesDepuis(t0);
        cout << left << setw(7)  << hauteurMap(m) << "| "
             << left << setw(12) << fixed << setprecision(1) << 2 * log2(n + 1.0) << "| "
             << left << setw(15) << fixed << setprecision(2) << ms << " |" << endl;
    }
    cout << "\nstd::map garde une hauteur en O(log n) : pas de lenteur O(n^2) et pas de stack overflow\n";
    cout << "(son insertion est une boucle, pas une recursion).\n";
    cout << "Solution : arbre equilibre (AVL, rouge-noir, std::map/std::set) ou insertion iterative.\n";
    return 0;
}
