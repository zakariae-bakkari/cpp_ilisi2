// Compilé dans libpile.so : instanciation explicite de PileListe<T>
// pour les types utilisés par les programmes du TP.
#include <string>
#include "PileListe.tpp"

template class PileListe<int>;
template class PileListe<double>;
template class PileListe<char>;
template class PileListe<std::string>;
