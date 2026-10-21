// Compilé dans libpile.so : instanciation explicite de PileTableau<T>
// pour les types utilisés par les programmes du TP.
#include <string>
#include "PileTableau.tpp"

template class PileTableau<int>;
template class PileTableau<double>;
template class PileTableau<char>;
template class PileTableau<std::string>;
