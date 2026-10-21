#include <iostream>
#include <queue>       // Nécessaire pour la FILE FIFO (std::queue) -> Parcours en Largeur (BFS)
#include <stack>       // Nécessaire pour la PILE LIFO (std::stack) -> Parcours en Profondeur (DFS)
#include <vector>      // Utile pour stocker ou retourner l'ordre des éléments visités
#include <memory>      // Optionnel : si vous souhaitez utiliser des smart pointers

using namespace std;

// ==============================================================================
// STRUCTURE DE NŒUD D'ARBRE BINAIRE
// ==============================================================================
struct Noeud {
    int valeur;
    Noeud* gauche;
    Noeud* droite;

    Noeud(int val) : valeur(val), gauche(nullptr), droite(nullptr) {}
};

/**
 * @brief Parcours en largeur (Breadth-First Search) d'un arbre binaire.
 * Affiche les valeurs des nœuds niveau par niveau.
 * 
 * @param racine Pointeur vers la racine de l'arbre
 * @return Une pile contenant les nœuds visités dans l'ordre du parcours en largeur.
 */

stack<Noeud*> parcoursLargeur(Noeud* racine) {
    stack<Noeud*> pile; 
    if(!racine) return pile; /* si la racine est nulle, on retourne une pile vide */

    queue<Noeud*> file; 
    file.push(racine);  // On commence par la racine
    
    while (!file.empty()) {
        Noeud* courant = file.front(); // On récupère le nœud en tête de file
        pile.push(courant); // On le met dans la pile (optionnel, pour un usage ultérieur)
        file.pop();                    // On le retire de la file
        cout << courant->valeur << " "; // On affiche sa valeur

        // On ajoute les enfants gauche et droit à la file s'ils existent
        if (courant->gauche) {
            file.push(courant->gauche);
        }
        if (courant->droite) {
            file.push(courant->droite);
        }
    }
    return pile;
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

// ==============================================================================
// MAIN DE TEST
// ==============================================================================
int main() {
    // Niveau 0 (Racine)
    Noeud* racine = new Noeud(7);

    // 1
    racine->gauche = new Noeud(9);
    racine->droite = new Noeud(67);

    // 2
    racine->gauche->gauche = new Noeud(1);
    racine->gauche->droite = new Noeud(28);
    racine->droite->gauche = new Noeud(8);
    racine->droite->droite = new Noeud(10);

    // 3
    racine->gauche->droite->gauche = new Noeud(29);
    racine->gauche->droite->droite = new Noeud(2);

    
    racine->droite->gauche->gauche = new Noeud(57);
    racine->droite->gauche->droite = new Noeud(40);

    
    racine->droite->droite->droite = new Noeud(6);

    cout << "parcours en largeur (BFS) : " << endl;
    stack<Noeud*> result = parcoursLargeur(racine);/* j'ai utiliser la fonction return du stack en cas du besoin */
    cout << endl;

    libererArbre(racine);
    return 0;
}
