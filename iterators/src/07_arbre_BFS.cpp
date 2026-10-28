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
 * @brief Algorithme de parcours en largeur (BFS) pur et simple.
 * Utilise deux files :
 * - fileAttente : file FIFO pour l'exploration niveau par niveau
 * - fileVisites : file FIFO qui stocke le résultat dans l'ordre de visite
 * 
 * @param racine Pointeur vers la racine de l'arbre
 * @return Une file contenant les nœuds visités
 */
queue<Noeud*> parcoursLargeur(Noeud* racine) {
    queue<Noeud*> fileVisites;
    if (!racine) return fileVisites;

    queue<Noeud*> fileAttente;
    fileAttente.push(racine);

    while (!fileAttente.empty()) {
        Noeud* courant = fileAttente.front();
        fileAttente.pop();
        fileVisites.push(courant);

        if (courant->gauche) {
            fileAttente.push(courant->gauche);
        }
        if (courant->droite) {
            fileAttente.push(courant->droite);
        }
    }

    return fileVisites;
}

// ==============================================================================
// FONCTION DE VISUALISATION : TRACÉ DÉTAILLÉ ÉTAPE PAR ÉTAPE
// ==============================================================================

/**
 * @brief Fonction séparée dédiée à l'affichage pédagogique du tracé pas à pas.
 * Permet de visualiser l'état des deux files sans encombrer parcoursLargeur().
 */
void tracerParcoursLargeur(Noeud* racine) {
    queue<Noeud*> fileVisites;
    if (!racine) return;

    queue<Noeud*> fileAttente;
    fileAttente.push(racine);

    cout << "\n========================================================================================================\n";
    cout << "  DÉTAIL ÉTAPE PAR ÉTAPE : ÉTAT DE LA FILE 1 (ATTENTE) ET DE LA FILE 2 (VISITÉS)\n";
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
        Noeud* courant = fileAttente.front();
        fileAttente.pop();
        fileVisites.push(courant);

        if (courant->gauche) fileAttente.push(courant->gauche);
        if (courant->droite) fileAttente.push(courant->droite);

        // Affichage de l'état après traitement
        cout << "| " << left << setw(8)  << ("#" + to_string(etape++))
             << "| " << left << setw(14) << courant->valeur
             << "| " << left << setw(38) << afficherContenuFile(fileAttente)
             << "| " << left << setw(36) << afficherContenuFile(fileVisites) << " |\n";
    }
    cout << "========================================================================================================\n";
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

    cout << "=================================================================" << endl;
    cout << " 1. PARCOURS EN LARGEUR PUR (parcoursLargeur) :" << endl;
    cout << "=================================================================" << endl;
    queue<Noeud*> result = parcoursLargeur(racine);

    cout << "Resultat (visite FIFO) : ";
    while (!result.empty()) {
        cout << result.front()->valeur << " ";
        result.pop();
    }
    cout << "\n\n";

    cout << "=================================================================" << endl;
    cout << " 2. TRACE ETAPE PAR ETAPE (tracerParcoursLargeur) :" << endl;
    cout << "=================================================================" << endl;
    tracerParcoursLargeur(racine);
    cout << endl;

    libererArbre(racine);
    return 0;
}
