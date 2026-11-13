#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdint>

using namespace std;
using namespace std::chrono;

// ==============================================================================
// INSERTION ET VALIDITE DES ITERATEURS : vector, map, unordered_map (cle, valeur)
// ==============================================================================
// Question : apres une insertion, un iterateur garde avant reste-t-il valide ?
//   - vector        : NON si le tableau est realloue (tout est deplace),
//                     NON pour les elements apres le point d'insertion (decales).
//   - map           : OUI toujours. Chaque paire est dans son propre noeud, qui
//                     ne bouge jamais : on ne fait que changer des pointeurs.
//   - unordered_map : NON si la table est "rehashee" (plus de cases), mais les
//                     references / pointeurs vers les paires restent valides.
// On ne dereference JAMAIS un iterateur invalide (comportement indefini) :
// on compare des adresses et on relit les cases avec v[i].

using Paire = pair<int, int>;  // (cle, valeur)

uintptr_t adresse(const void* p) { return reinterpret_cast<uintptr_t>(p); }

string ouiNon(bool valide) { return valide ? "VALIDE" : "INVALIDE"; }

// ------------------------------------------------------------------------------
// Partie 1 : demonstrations
// ------------------------------------------------------------------------------
void demonstrations() {
    cout << "PARTIE 1 : DEMONSTRATIONS (on garde un iterateur sur la cle 20)\n\n";

    // 1) vector plein : inserer 0 au debut -> reallocation
    {
        vector<Paire> v = {{10, 100}, {20, 200}, {30, 300}};
        v.shrink_to_fit();
        auto it = v.begin() + 1;  // sur (20, 200)
        uintptr_t avant = adresse(v.data());
        size_t capAvant = v.capacity();
        v.insert(v.begin(), {0, 0});
        bool realloue = adresse(v.data()) != avant;
        (void)it;  // ne plus l'utiliser
        cout << "1) vector plein (capacite " << capAvant << "), insert de (0,0) au debut :\n"
             << "   capacite " << capAvant << " -> " << v.capacity()
             << ", tableau " << (realloue ? "DEPLACE ailleurs en memoire" : "au meme endroit") << "\n"
             << "   -> iterateur " << ouiNon(false)
             << " : il pointe vers l'ancien tableau, qui est libere.\n\n";
    }

    // 2) vector avec de la place : inserer 0 au debut -> decalage
    {
        vector<Paire> v = {{10, 100}, {20, 200}, {30, 300}};
        v.reserve(10);
        auto it = v.begin() + 1;  // sur (20, 200)
        uintptr_t avant = adresse(v.data());
        v.insert(v.begin(), {0, 0});
        (void)it;
        cout << "2) vector avec de la place (capacite 10), insert de (0,0) au debut :\n"
             << "   pas de reallocation (tableau " << (adresse(v.data()) == avant ? "au meme endroit" : "deplace")
             << "), mais tout est decale d'une case.\n"
             << "   La case de l'iterateur contient maintenant (" << v[1].first << "," << v[1].second
             << ") au lieu de (20,200)\n"
             << "   -> iterateur " << ouiNon(false) << " : il ne designe plus le meme element.\n\n";
    }

    // 3) vector avec de la place : push_back a la fin -> rien ne bouge avant
    {
        vector<Paire> v = {{10, 100}, {20, 200}, {30, 300}};
        v.reserve(10);
        auto it = v.begin() + 1;
        v.push_back({40, 400});
        cout << "3) vector avec de la place, push_back de (40,400) a la fin :\n"
             << "   aucun element deplace, *it = (" << it->first << "," << it->second << ")\n"
             << "   -> iterateur " << ouiNon(true) << " (seul end() change).\n\n";
    }

    // 4) map : inserer 0 puis 100 000 cles
    {
        map<int, int> m = {{10, 100}, {20, 200}, {30, 300}};
        auto it = m.find(20);
        m.insert({0, 0});
        for (int k = 1000; k < 101000; k++) m.insert({k, k * 10});
        cout << "4) map, insert de (0,0) puis de 100 000 autres paires :\n"
             << "   it->first = " << it->first << ", it->second = " << it->second << "\n"
             << "   -> iterateur " << ouiNon(it->first == 20 && it->second == 200)
             << " : le noeud de (20,200) n'a jamais bouge, seuls des pointeurs ont change.\n\n";
    }

    // 5) unordered_map : inserer 0 puis 100 000 cles -> rehash
    {
        unordered_map<int, int> u = {{10, 100}, {20, 200}, {30, 300}};
        auto it = u.find(20);
        const Paire* p = reinterpret_cast<const Paire*>(&*it);  // adresse de la paire
        size_t casesAvant = u.bucket_count();
        u.insert({0, 0});
        for (int k = 1000; k < 101000; k++) u.insert({k, k * 10});
        bool rehash = u.bucket_count() != casesAvant;
        bool memeAdresse = adresse(&*u.find(20)) == adresse(p);
        (void)it;
        cout << "5) unordered_map, insert de (0,0) puis de 100 000 autres paires :\n"
             << "   cases : " << casesAvant << " -> " << u.bucket_count()
             << (rehash ? " (rehash : les paires sont redistribuees)" : "") << "\n"
             << "   -> iterateur " << ouiNon(!rehash) << " : apres un rehash, l'ordre de parcours change.\n"
             << "   -> reference / pointeur vers (20,200) " << ouiNon(memeAdresse)
             << " : la paire est restee a la meme adresse.\n\n";
    }

    // 6) suppression d'une autre cle
    {
        map<int, int> m = {{10, 100}, {20, 200}, {30, 300}};
        auto it = m.find(20);
        m.erase(10);
        cout << "6) map, erase(10) : it->first = " << it->first << " -> iterateur " << ouiNon(true)
             << " (seul l'element supprime est invalide).\n"
             << "   vector, erase(begin()) : tout est decale vers la gauche -> iterateurs apres "
                "le point de suppression " << ouiNon(false) << ".\n\n";
    }
}

// ------------------------------------------------------------------------------
// Partie 2 : les trois scenarios, n paires (cle, valeur)
// ------------------------------------------------------------------------------
template <class F> double ms(F f) {
    auto t0 = high_resolution_clock::now();
    f();
    return duration<double, milli>(high_resolution_clock::now() - t0).count();
}

// Les resultats des recherches sont ecrits ici : sans ca, le compilateur
// supprime les boucles (leur resultat ne servirait a rien) et on mesurerait 0 ms.
volatile long long puits;

string duree(double ms) {
    ostringstream s;
    s << fixed;
    if (ms < 1000) s << setprecision(1) << ms << " ms";
    else s << setprecision(2) << ms / 1000 << " s ";
    return s.str();
}

struct Resultat {
    string nom;
    double insertion, recherche;      // recherche < 0 : non mesuree
    long long invalidations;          // reallocations (vector) ou rehash (unordered_map)
    long long decales;                // elements deplaces par les insertions au milieu
    string iterateur, reference;      // l'iterateur / la reference sur la 1re paire
};

// vector trie : chaque paire est inseree a sa place (lower_bound + insert)
Resultat vectorTrie(const vector<int>& cles) {
    Resultat r{"vector trie", 0, 0, 0, 0, "", ""};
    vector<Paire> v;
    size_t indiceGarde = 0;
    bool valide = true;
    r.insertion = ms([&] {
        for (size_t i = 0; i < cles.size(); i++) {
            auto pos = lower_bound(v.begin(), v.end(), Paire{cles[i], 0});
            size_t indice = pos - v.begin();
            size_t cap = v.capacity();
            r.decales += v.size() - indice;
            v.insert(pos, {cles[i], cles[i] * 10});
            if (v.capacity() != cap) { r.invalidations++; if (i > 0) valide = false; }
            if (i > 0 && indice <= indiceGarde) { indiceGarde++; valide = false; }
        }
    });
    long long trouves = 0;
    r.recherche = ms([&] {
        for (int c : cles) trouves += binary_search(v.begin(), v.end(), Paire{c, c * 10});
        puits = trouves;
    });
    r.iterateur = valide ? "valide" : "invalide";
    r.reference = r.iterateur;  // pour un vector, reference et iterateur meurent ensemble
    return r;
}

// vector non trie : push_back a la fin
Resultat vectorPushBack(const vector<int>& cles) {
    Resultat r{"vector (push_back)", 0, -1, 0, 0, "", ""};
    vector<Paire> v;
    bool valide = true;
    r.insertion = ms([&] {
        for (size_t i = 0; i < cles.size(); i++) {
            size_t cap = v.capacity();
            v.push_back({cles[i], cles[i] * 10});
            if (v.capacity() != cap) { r.invalidations++; if (i > 0) valide = false; }
        }
    });
    r.iterateur = r.reference = valide ? "valide" : "invalide";
    return r;
}

Resultat carte(const vector<int>& cles) {
    Resultat r{"map", 0, 0, 0, 0, "", ""};
    map<int, int> m;
    map<int, int>::iterator garde;
    r.insertion = ms([&] {
        for (size_t i = 0; i < cles.size(); i++) {
            auto res = m.insert({cles[i], cles[i] * 10});
            if (i == 0) garde = res.first;
        }
    });
    long long trouves = 0;
    r.recherche = ms([&] { for (int c : cles) trouves += m.count(c); puits = trouves; });
    bool ok = garde->first == cles[0] && garde->second == cles[0] * 10;
    r.iterateur = r.reference = ok ? "valide" : "invalide";
    return r;
}

Resultat tableHachage(const vector<int>& cles) {
    Resultat r{"unordered_map", 0, 0, 0, 0, "", ""};
    unordered_map<int, int> u;
    uintptr_t adresseGarde = 0;
    r.insertion = ms([&] {
        for (size_t i = 0; i < cles.size(); i++) {
            size_t cases = u.bucket_count();
            auto res = u.insert({cles[i], cles[i] * 10});
            if (i == 0) adresseGarde = adresse(&*res.first);
            else if (u.bucket_count() != cases) r.invalidations++;
        }
    });
    long long trouves = 0;
    r.recherche = ms([&] { for (int c : cles) trouves += u.count(c); puits = trouves; });
    r.iterateur = r.invalidations == 0 ? "valide" : "invalide";
    r.reference = adresse(&*u.find(cles[0])) == adresseGarde ? "valide" : "invalide";
    return r;
}

// n cles 1..n rangees selon le type (comme le programme 15)
vector<int> generer(int n, const string& type, mt19937& gen) {
    vector<int> v(n);
    for (int i = 0; i < n; i++) v[i] = i + 1;
    if (type == "aleatoires") shuffle(v.begin(), v.end(), gen);
    if (type == "presque triees")
        for (int k = 0; k < n / 10; k++) swap(v[gen() % n], v[gen() % n]);
    return v;
}

string nombre(long long v) {
    string s = to_string(v);
    for (int i = (int)s.size() - 3; i > 0; i -= 3) s.insert(i, " ");
    return s;
}

void scenarios(int n) {
    cout << "PARTIE 2 : " << n << " PAIRES (cle, valeur), TROIS SCENARIOS\n";
    string sep = "+----------------+--------------------+------------+------------+---------------+-----------------+------------+------------+\n";
    cout << sep
         << "| Donnees        | Structure          |  Insertion |  Recherche | Invalidations |        Elements | Iterateur  | Reference  |\n"
         << "|                |                    |            | des n cles |  (realloc. ou |         decales | sur la 1re | sur la 1re |\n"
         << "|                |                    |            |            |       rehash) |                 | paire      | paire      |\n"
         << sep;
    mt19937 gen(2026);
    for (string type : {"aleatoires", "triees", "presque triees"}) {
        vector<int> cles = generer(n, type, gen);
        for (const Resultat& r : {vectorTrie(cles), vectorPushBack(cles), carte(cles), tableHachage(cles)}) {
            cout << "| " << left << setw(14) << type << " | " << setw(18) << r.nom << right
                 << " | " << setw(10) << duree(r.insertion)
                 << " | " << setw(10) << (r.recherche < 0 ? "-" : duree(r.recherche))
                 << " | " << setw(13) << nombre(r.invalidations)
                 << " | " << setw(15) << nombre(r.decales)
                 << " | " << left << setw(10) << r.iterateur << " | " << setw(10) << r.reference
                 << right << " |\n";
        }
        cout << sep;
    }
    cout << "vector (push_back) : non trie, donc pas de recherche rapide (il faudrait tout parcourir).\n"
         << "Elements decales : total des elements deplaces d'une case par les insertions au milieu.\n";
}

int main() {
    demonstrations();
    scenarios(100000);
    return 0;
}
