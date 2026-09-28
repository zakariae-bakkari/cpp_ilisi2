#ifndef PILE_LISTE_TPP
#define PILE_LISTE_TPP

// Implémentation de PileListe<T>.
// Inclus par src/PileListe.cpp (compilé dans libpile.so) et, si besoin,
// par un programme client qui utilise un type absent de la bibliothèque.

#include <stdexcept>
#include "PileListe.h"

template <typename T>
void PileListe<T>::vider() {
    while (tete != nullptr) {
        Noeud* tmp = tete;
        tete = tete->suivant;
        delete tmp;
    }
    nb = 0;
}

template <typename T>
void PileListe<T>::copier(const PileListe& p) {
    tete = nullptr;
    nb = p.nb;
    Noeud** dernier = &tete;
    for (Noeud* n = p.tete; n != nullptr; n = n->suivant) {
        *dernier = new Noeud(n->valeur);
        dernier = &(*dernier)->suivant;
    }
}

template <typename T>
PileListe<T>::PileListe() : tete(nullptr), nb(0) {}

template <typename T>
PileListe<T>::PileListe(const PileListe& p) { copier(p); }

template <typename T>
PileListe<T>& PileListe<T>::operator=(const PileListe& p) {
    if (this != &p) {
        vider();
        copier(p);
    }
    return *this;
}

template <typename T>
PileListe<T>::~PileListe() { vider(); }

template <typename T>
void PileListe<T>::empiler(const T& x) {
    tete = new Noeud(x, tete);   // insertion en tête
    nb++;
}

template <typename T>
T PileListe<T>::depiler() {
    if (estVide())
        throw std::underflow_error("Pile vide");
    Noeud* tmp = tete;
    T v = tmp->valeur;
    tete = tete->suivant;
    delete tmp;
    nb--;
    return v;
}

template <typename T>
const T& PileListe<T>::getSommet() const {
    if (estVide())
        throw std::underflow_error("Pile vide");
    return tete->valeur;
}

template <typename T>
bool PileListe<T>::estVide() const { return tete == nullptr; }

template <typename T>
int PileListe<T>::taille() const { return nb; }

template <typename T>
void PileListe<T>::afficher(std::ostream& os) const {
    os << "[ ";
    for (Noeud* n = tete; n != nullptr; n = n->suivant)
        os << n->valeur << " ";
    os << "]";
}

#endif
