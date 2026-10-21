// Compilé dans libpile.so : fonctions utilitaires de l'analyseur
// et instanciation explicite de Analyseur<PileTableau> / Analyseur<PileListe>.
#include <cctype>
#include <cmath>
#include <sstream>
#include "Expression.tpp"
#include "PileListe.tpp"
#include "PileTableau.tpp"

std::ostream& operator<<(std::ostream& os, const Token& t) {
    return os << t.texte;
}

bool estOuvrante(char c) { return c == '(' || c == '[' || c == '{'; }
bool estFermante(char c) { return c == ')' || c == ']' || c == '}'; }
bool estOperateur(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

char ouvranteAssociee(char fermante) {
    switch (fermante) {
        case ')': return '(';
        case ']': return '[';
        default:  return '{';
    }
}

int rangDelimiteur(char c) {
    switch (c) {
        case '(': return 1;
        case '[': return 2;
        default:  return 3;   // '{'
    }
}

int priorite(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^':           return 3;
        default:            return 0;
    }
}

bool associatifDroite(char op) { return op == '^'; }

std::vector<Token> decouper(const std::string& expr) {
    std::vector<Token> tokens;
    int n = expr.size();
    int i = 0;
    while (i < n) {
        char c = expr[i];
        if (std::isspace((unsigned char)c)) {
            i++;
        } else if (std::isdigit((unsigned char)c)) {
            int debut = i;
            while (i < n && std::isdigit((unsigned char)expr[i])) i++;
            if (i < n && expr[i] == '.') {
                i++;
                while (i < n && std::isdigit((unsigned char)expr[i])) i++;
            }
            tokens.push_back({NOMBRE, expr.substr(debut, i - debut), debut});
        } else if (std::isalpha((unsigned char)c) || c == '_') {
            int debut = i;
            while (i < n && (std::isalnum((unsigned char)expr[i]) || expr[i] == '_')) i++;
            tokens.push_back({VARIABLE, expr.substr(debut, i - debut), debut});
        } else if (estOperateur(c)) {
            tokens.push_back({OPERATEUR, std::string(1, c), i++});
        } else if (estOuvrante(c)) {
            tokens.push_back({OUVRANTE, std::string(1, c), i++});
        } else if (estFermante(c)) {
            tokens.push_back({FERMANTE, std::string(1, c), i++});
        } else {
            throw ErreurExpression(std::string("Caractere non autorise '") + c + "'", i);
        }
    }
    return tokens;
}

bool estNombre(const std::string& s) {
    if (s.empty() || !std::isdigit((unsigned char)s[0])) return false;
    std::istringstream is(s);
    double d;
    is >> d;
    return is.eof() && !is.fail();
}

bool estIdentificateur(const std::string& s) {
    if (s.empty() || !(std::isalpha((unsigned char)s[0]) || s[0] == '_')) return false;
    for (char c : s)
        if (!(std::isalnum((unsigned char)c) || c == '_')) return false;
    return true;
}

double appliquer(char op, double a, double b) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw std::domain_error("Division par zero");
            return a / b;
        default:  return std::pow(a, b);   // '^'
    }
}

template class PileTableau<Token>;
template class PileListe<Token>;
template class Analyseur<PileTableau>;
template class Analyseur<PileListe>;
