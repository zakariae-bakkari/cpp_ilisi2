#ifndef PILE_TABLEAU_H
#define PILE_TABLEAU_H

#include <iostream>
#include <string>
#include "Pile.h"

// Pile générique implémentée avec un tableau dynamique.
// Le sommet est la dernière case occupée : tab[nb - 1].
//
// Ce fichier ne contient que la déclaration : le code des méthodes est dans
// PileTableau.tpp et il est compilé dans la bibliothèque partagée libpile.so
// pour les types courants (voir les "extern template" en bas du fichier).
// Pour un autre type T, inclure "PileTableau.tpp" dans le programme client.
template <typename T>
class PileTableau : public Pile<T> {
private:
    T* tab;         // tableau alloué dynamiquement
    int capacite;   // taille du tableau
    int nb;         // nombre d'éléments (indice de la prochaine case libre)

    // double la capacité quand le tableau est plein : coût amorti O(1)
    void agrandir();

public:
    explicit PileTableau(int cap = 4);
    PileTableau(const PileTableau& p);              // copie profonde
    PileTableau& operator=(const PileTableau& p);   // affectation
    ~PileTableau();

    void empiler(const T& x) override;
    T depiler() override;
    const T& getSommet() const override;
    bool estVide() const override;
    int taille() const override;
    int getCapacite() const;

    // affiche du sommet vers la base
    void afficher(std::ostream& os = std::cout) const;
};

// Instanciations fournies par libpile.so : le compilateur ne les régénère
// pas dans le programme client, il utilise celles de la bibliothèque.
extern template class PileTableau<int>;
extern template class PileTableau<double>;
extern template class PileTableau<char>;
extern template class PileTableau<std::string>;

#endif
