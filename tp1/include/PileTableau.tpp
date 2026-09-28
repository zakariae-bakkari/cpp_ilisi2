#ifndef PILE_TABLEAU_TPP
#define PILE_TABLEAU_TPP

// Implémentation de PileTableau<T>.
// Inclus par src/PileTableau.cpp (compilé dans libpile.so) et, si besoin,
// par un programme client qui utilise un type absent de la bibliothèque.

#include <stdexcept>
#include "PileTableau.h"

template <typename T>
void PileTableau<T>::agrandir() {
    int nouvelleCapacite = capacite * 2;
    T* nouveau = new T[nouvelleCapacite];
    for (int i = 0; i < nb; i++)
        nouveau[i] = tab[i];
    delete[] tab;
    tab = nouveau;
    capacite = nouvelleCapacite;
}

template <typename T>
PileTableau<T>::PileTableau(int cap)
    : tab(nullptr), capacite(cap < 1 ? 1 : cap), nb(0) {
    tab = new T[capacite];
}

template <typename T>
PileTableau<T>::PileTableau(const PileTableau& p)
    : tab(new T[p.capacite]), capacite(p.capacite), nb(p.nb) {
    for (int i = 0; i < nb; i++)
        tab[i] = p.tab[i];
}

template <typename T>
PileTableau<T>& PileTableau<T>::operator=(const PileTableau& p) {
    if (this != &p) {
        T* nouveau = new T[p.capacite];   // allouer avant de libérer
        for (int i = 0; i < p.nb; i++)
            nouveau[i] = p.tab[i];
        delete[] tab;
        tab = nouveau;
        capacite = p.capacite;
        nb = p.nb;
    }
    return *this;
}

template <typename T>
PileTableau<T>::~PileTableau() { delete[] tab; }

template <typename T>
void PileTableau<T>::empiler(const T& x) {
    if (nb == capacite)
        agrandir();
    tab[nb++] = x;
}

template <typename T>
T PileTableau<T>::depiler() {
    if (estVide())
        throw std::underflow_error("Pile vide");
    return tab[--nb];
}

template <typename T>
const T& PileTableau<T>::getSommet() const {
    if (estVide())
        throw std::underflow_error("Pile vide");
    return tab[nb - 1];
}

template <typename T>
bool PileTableau<T>::estVide() const { return nb == 0; }

template <typename T>
int PileTableau<T>::taille() const { return nb; }

template <typename T>
int PileTableau<T>::getCapacite() const { return capacite; }

template <typename T>
void PileTableau<T>::afficher(std::ostream& os) const {
    os << "[ ";
    for (int i = nb - 1; i >= 0; i--)
        os << tab[i] << " ";
    os << "]";
}

#endif
