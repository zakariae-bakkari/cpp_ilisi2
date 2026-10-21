#include <iostream>
#include <queue>       // Nécessaire pour la FILE FIFO (std::queue) -> Parcours en Largeur (BFS)
#include <stack>       // Nécessaire pour la PILE LIFO (std::stack) -> Stockage des éléments visités
#include <vector>      // Utile pour inspecter le contenu de la pile
#include <iomanip>     // Pour un affichage sous forme de tableau propre
#include <string>

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

// ==============================================================================
// FONCTIONS UTILITAIRES : VISUALISATION DU CONTENU DE LA FILE ET DE LA PILE
// ==============================================================================

// Retourne une représentation textuelle de la FILE (du front vers le back)
// On passe par valeur pour travailler sur une copie et ne pas vider la vraie file
string afficherContenuFile(queue<Noeud*> f) {
    if (f.empty()) return "[] (vide)";
    string s = "[";
    while (!f.empty()) {
        s += to_string(f.front()->valeur);
        f.pop();
        if (!f.empty()) s += ", ";
    }
    s += "]";
    return s;
}

// Retourne une représentation textuelle de la PILE (du bas vers le haut = ordre d'insertion)
// On passe par valeur pour travailler sur une copie et ne pas vider la vraie pile
string afficherContenuPile(stack<Noeud*> p) {
    if (p.empty()) return "[] (vide)";
    vector<int> elements;
    while (!p.empty()) {
        elements.push_back(p.top()->valeur);
        p.pop();
    }
    string s = "[";
    // On parcourt en sens inverse pour afficher de la base (premier visité) au sommet (dernier visité)
    for (int i = (int)elements.size() - 1; i >= 0; --i) {
        s += to_string(elements[i]);
        if (i > 0) s += ", ";
    }
    s += "]";
    return s;
}

/**
 * @brief Parcours en largeur (Breadth-First Search) d'un arbre binaire.
 * Affiche l'état de la FILE (non visités) et de la PILE (visités) à chaque étape.
 * 
 * @param racine Pointeur vers la racine de l'arbre
 * @return Une pile contenant les nœuds visités dans l'ordre du parcours.
 */
stack<Noeud*> parcoursLargeur(Noeud* racine) {
    stack<Noeud*> pile; 
    if(!racine) return pile; /* si la racine est nulle, on retourne une pile vide */

    queue<Noeud*> file; 
    file.push(racine);  // On commence par la racine

    cout << "\n========================================================================================================\n";
    cout << "  DÉTAIL ÉTAPE PAR ÉTAPE : ÉTAT DE LA FILE (NON VISITÉ) ET DE LA PILE (VISITÉ)\n";
    cout << "========================================================================================================\n";
    cout << "| " << left << setw(8)  << "Etape"
         << "| " << left << setw(14) << "Noeud traite"
         << "| " << left << setw(38) << "FILE : Non visites (en attente / FIFO)"
         << "| " << left << setw(36) << "PILE : Visites (historique)" << " |\n";
    cout << "|---------|---------------|---------------------------------------|--------------------------------------|\n";

    // État initial (avant d'entrer dans la boucle)
    cout << "| " << left << setw(8)  << "Init"
         << "| " << left << setw(14) << "-"
         << "| " << left << setw(38) << afficherContenuFile(file)
         << "| " << left << setw(36) << afficherContenuPile(pile) << " |\n";

    int etape = 1;
    while (!file.empty()) {
        Noeud* courant = file.front(); // On récupère le nœud en tête de file
        file.pop();                    // On le retire de la file
        pile.push(courant);            // On l'ajoute à la pile des éléments visités

        // On ajoute les enfants gauche et droit à la file s'ils existent
        if (courant->gauche) {
            file.push(courant->gauche);
        }
        if (courant->droite) {
            file.push(courant->droite);
        }

        // Affichage de l'état après traitement de ce nœud
        cout << "| " << left << setw(8)  << ("#" + to_string(etape++))
             << "| " << left << setw(14) << courant->valeur
             << "| " << left << setw(38) << afficherContenuFile(file)
             << "| " << left << setw(36) << afficherContenuPile(pile) << " |\n";
    }
    cout << "========================================================================================================\n";

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

    cout << "PARCOURS EN LARGEUR (BFS) DE L'ARBRE :" << endl;
    stack<Noeud*> result = parcoursLargeur(racine);

    cout << "\nDepilage de la PILE retournee (Ordre inverse LIFO) :\n  ";
    while (!result.empty()) {
        cout << result.top()->valeur << " ";
        result.pop();
    }
    cout << "\n\n";

    libererArbre(racine);
    return 0;
}
