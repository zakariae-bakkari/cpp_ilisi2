#ifndef PILE_H
#define PILE_H

#include <stdexcept>

// Interface générique d'une pile (LIFO : dernier entré, premier sorti).
// Les implémentations concrètes (tableau dynamique, liste chaînée)
// respectent ce contrat : le code client peut manipuler une Pile<T>&
// sans connaître la représentation interne.
template <typename T>
class Pile {
public:
    virtual ~Pile() {}

    virtual void empiler(const T& x) = 0;       // ajoute x au sommet
    virtual T depiler() = 0;                    // retire et renvoie le sommet
    virtual const T& getSommet() const = 0;     // consulte le sommet
    virtual bool estVide() const = 0;
    virtual int taille() const = 0;
};

#endif
