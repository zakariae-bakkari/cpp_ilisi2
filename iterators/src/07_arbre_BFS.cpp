#include <iostream>
#include <queue>       // Nécessaire pour les DEUX FILES FIFO (std::queue)
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
// FONCTION UTILITAIRE : VISUALISATION DU CONTENU D'UNE FILE (std::queue)
// ==============================================================================

// Retourne une représentation textuelle de la FILE (du front vers le back)
// On passe par valeur (copie locale) pour ne pas vider la vraie file
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

/**
 * @brief Parcours en largeur (Breadth-First Search) d'un arbre binaire avec DEUX FILES.
 * - File 1 (fileAttente) : Nœuds en attente d'exploration (non visités)
 * - File 2 (fileVisites) : Nœuds déjà explorés (visités, dans l'ordre chronologique)
 * 
 * @param racine Pointeur vers la racine de l'arbre
 * @return Une file contenant les nœuds visités dans l'ordre du parcours.
 */
queue<Noeud*> parcoursLargeur(Noeud* racine) {
    queue<Noeud*> fileVisites; // File 2 : stocke les nœuds visités
    if (!racine) return fileVisites; /* si la racine est nulle, on retourne une file vide */

    queue<Noeud*> fileAttente; // File 1 : gère l'exploration BFS
    fileAttente.push(racine);  // On commence par la racine

    cout << "\n========================================================================================================\n";
    cout << "  DÉTAIL ÉTAPE PAR ÉTAPE : PARCOURS EN LARGEUR AVEC DEUX FILES (FIFO)\n";
    cout << "========================================================================================================\n";
    cout << "| " << left << setw(8)  << "Etape"
         << "| " << left << setw(14) << "Noeud traite"
         << "| " << left << setw(38) << "FILE 1 : Non visites (en attente)"
         << "| " << left << setw(36) << "FILE 2 : Visites (historique BFS)" << " |\n";
    cout << "|---------|---------------|---------------------------------------|--------------------------------------|\n";

    // État initial (avant d'entrer dans la boucle)
    cout << "| " << left << setw(8)  << "Init"
         << "| " << left << setw(14) << "-"
         << "| " << left << setw(38) << afficherContenuFile(fileAttente)
         << "| " << left << setw(36) << afficherContenuFile(fileVisites) << " |\n";

    int etape = 1;
    while (!fileAttente.empty()) {
        Noeud* courant = fileAttente.front(); // On récupère le nœud en tête de la file d'attente
        fileAttente.pop();                    // On le retire de la file d'attente
        fileVisites.push(courant);            // On l'ajoute à la file des éléments visités

        // On ajoute les enfants gauche et droit à la file d'attente s'ils existent
        if (courant->gauche) {
            fileAttente.push(courant->gauche);
        }
        if (courant->droite) {
            fileAttente.push(courant->droite);
        }

        // Affichage de l'état après traitement de ce nœud
        cout << "| " << left << setw(8)  << ("#" + to_string(etape++))
             << "| " << left << setw(14) << courant->valeur
             << "| " << left << setw(38) << afficherContenuFile(fileAttente)
             << "| " << left << setw(36) << afficherContenuFile(fileVisites) << " |\n";
    }
    cout << "========================================================================================================\n";

    return fileVisites;
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
    queue<Noeud*> result = parcoursLargeur(racine);

    cout << "\nLecture de la FILE retournee (Ordre chronologique FIFO) :\n  ";
    while (!result.empty()) {
        cout << result.front()->valeur << " ";
        result.pop();
    }
    cout << "\n\n";

    libererArbre(racine);
    return 0;
}
