#ifndef PILE_LISTE_H
#define PILE_LISTE_H

#include <iostream>
#include <string>
#include "Pile.h"

// Pile générique implémentée avec une liste simplement chaînée.
// Le sommet est la tête de liste : empiler/dépiler en O(1).
//
// Ce fichier ne contient que la déclaration : le code des méthodes est dans
// PileListe.tpp et il est compilé dans la bibliothèque partagée libpile.so
// pour les types courants (voir les "extern template" en bas du fichier).
// Pour un autre type T, inclure "PileListe.tpp" dans le programme client.
template <typename T>
class PileListe : public Pile<T> {
private:
    struct Noeud {
        T valeur;
        Noeud* suivant;
        Noeud(const T& v, Noeud* s = nullptr) : valeur(v), suivant(s) {}
    };

    Noeud* tete;
    int nb;

    void vider();
    void copier(const PileListe& p);   // copie les noeuds de p dans le même ordre

public:
    PileListe();
    PileListe(const PileListe& p);
    PileListe& operator=(const PileListe& p);
    ~PileListe();

    void empiler(const T& x) override;
    T depiler() override;
    const T& getSommet() const override;
    bool estVide() const override;
    int taille() const override;

    // affiche du sommet vers la base
    void afficher(std::ostream& os = std::cout) const;
};

// Instanciations fournies par libpile.so
extern template class PileListe<int>;
extern template class PileListe<double>;
extern template class PileListe<char>;
extern template class PileListe<std::string>;

#endif
