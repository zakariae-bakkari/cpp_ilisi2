#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <numeric>
#include <random>

using namespace std;
using namespace std::chrono;

// ==============================================================================
// UTILITAIRE DE CHRONOMÉTRAGE
// ==============================================================================
double get_ms(time_point<high_resolution_clock> start, time_point<high_resolution_clock> end) {
    return duration<double, milli>(end - start).count();
}

void print_header(const string& title) {
    cout << "\n================================================================================\n";
    cout << "  " << title << "\n";
    cout << "================================================================================\n";
    cout << "| " << left << setw(38) << "Operation Concrete"
         << "| " << setw(13) << "std::vector"
         << "| " << setw(13) << "std::list"
         << "| " << setw(10) << "Vainqueur" << " |\n";
    cout << "|---------------------------------------|--------------|--------------|------------|\n";
}

void print_result(const string& operation, double t_vec, double t_lst, const string& explanation = "") {
    string vainqueur = (t_vec < t_lst) ? "vector" : "list";
    double ratio = (t_vec < t_lst) ? (t_lst / (t_vec > 0.0001 ? t_vec : 0.0001)) 
                                   : (t_vec / (t_lst > 0.0001 ? t_lst : 0.0001));

    cout << "| " << left << setw(38) << operation
         << "| " << right << setw(10) << fixed << setprecision(3) << t_vec << " ms "
         << "| " << right << setw(10) << fixed << setprecision(3) << t_lst << " ms "
         << "| " << left << setw(10) << vainqueur << " |\n";

    if (!explanation.empty()) {
        cout << "  -> Explication : " << explanation << " (" << vainqueur << " ~" 
             << fixed << setprecision(1) << ratio << "x plus rapide)\n";
    }
}

// ==============================================================================
// 1. CAS D'USAGE RÉEL : GESTIONNAIRE D'ÉTUDIANTS (SCOLARITÉ UNIVERSITAIRE)
// ==============================================================================
struct Etudiant {
    int id;
    string nom;
    double noteMoyenne;
    string filiere;

    bool operator<(const Etudiant& other) const {
        return noteMoyenne > other.noteMoyenne; // Tri par note décroissante (Top étudiants)
    }
};

void run_use_case_etudiants() {
    print_header("CAS D'USAGE 1 : SCOLARITÉ UNIVERSITAIRE (50 000 ÉTUDIANTS)");

    const int NB_ETUDIANTS = 50000;
    vector<Etudiant> v_etudiants;
    v_etudiants.reserve(NB_ETUDIANTS);
    list<Etudiant> l_etudiants;

    mt19937 rng(42);
    uniform_real_distribution<double> distNote(5.0, 20.0);

    for (int i = 0; i < NB_ETUDIANTS; ++i) {
        Etudiant e{i + 1, "Etudiant_" + to_string(i + 1), distNote(rng), (i % 2 == 0) ? "Informatique" : "Genie_Civil"};
        v_etudiants.push_back(e);
        l_etudiants.push_back(e);
    }

    // 1.A : Recherche d'un étudiant par son matricule/ID (std::find_if répété 50 fois)
    const int CIBLE_ID = 48500;
    volatile int dummy = 0;
    auto t1 = high_resolution_clock::now();
    for (int rep = 0; rep < 50; ++rep) {
        auto it = find_if(v_etudiants.begin(), v_etudiants.end(), [CIBLE_ID](const Etudiant& e) {
            return e.id == CIBLE_ID;
        });
        if (it != v_etudiants.end()) dummy += it->id;
    }
    auto t2 = high_resolution_clock::now();
    double t_find_vec = get_ms(t1, t2);

    t1 = high_resolution_clock::now();
    for (int rep = 0; rep < 50; ++rep) {
        auto it = find_if(l_etudiants.begin(), l_etudiants.end(), [CIBLE_ID](const Etudiant& e) {
            return e.id == CIBLE_ID;
        });
        if (it != l_etudiants.end()) dummy += it->id;
    }
    t2 = high_resolution_clock::now();
    double t_find_lst = get_ms(t1, t2);

    print_result("1. Recherche etudiant (50 scans)", t_find_vec, t_find_lst,
                 "Vector beneficie du hardware prefetcher CPU grace a la contiguite memoire");

    // 1.B : Calcul de la moyenne de promotion (50 calculs complets)
    volatile double dummy_sum = 0.0;
    t1 = high_resolution_clock::now();
    for (int rep = 0; rep < 50; ++rep) {
        double somme = 0.0;
        for (const auto& e : v_etudiants) somme += e.noteMoyenne;
        dummy_sum += somme;
    }
    t2 = high_resolution_clock::now();
    double t_moy_vec = get_ms(t1, t2);

    t1 = high_resolution_clock::now();
    for (int rep = 0; rep < 50; ++rep) {
        double somme = 0.0;
        for (const auto& e : l_etudiants) somme += e.noteMoyenne;
        dummy_sum += somme;
    }
    t2 = high_resolution_clock::now();
    double t_moy_lst = get_ms(t1, t2);
    (void)dummy; (void)dummy_sum;

    print_result("2. Calcul moyenne generale (50x)", t_moy_vec, t_moy_lst,
                 "Cache L1/L2 hits massifs pour vector lors du scan cumulatif");

    // 1.C : Classement de la promotion (Tri des 50 000 étudiants)
    // std::sort pour vector (Introsort O(N log N)), l.sort() pour list (MergeSort)
    t1 = high_resolution_clock::now();
    sort(v_etudiants.begin(), v_etudiants.end());
    t2 = high_resolution_clock::now();
    double t_sort_vec = get_ms(t1, t2);

    t1 = high_resolution_clock::now();
    l_etudiants.sort();
    t2 = high_resolution_clock::now();
    double t_sort_lst = get_ms(t1, t2);

    print_result("3. Classement du merite (Tri 50k)", t_sort_vec, t_sort_lst,
                 "Introsort vectoriel tire parti de l'arithmetique de pointeurs directe");

    // 1.D : Recherche dichotomique sur liste d'étudiants triée (1 000 recherches)
    // Vector possède des itérateurs Random Access -> std::lower_bound en O(log N) (16 sauts mémoire)
    // List possède des itérateurs Bidirectionnels -> std::lower_bound en O(N) (doit avancer nœud par nœud !)
    Etudiant etudiant_recherche{0, "", 14.50, ""};
    auto cmp_note = [](const Etudiant& a, const Etudiant& b) {
        return a.noteMoyenne > b.noteMoyenne;
    };

    t1 = high_resolution_clock::now();
    for (int rep = 0; rep < 1000; ++rep) {
        auto it = lower_bound(v_etudiants.begin(), v_etudiants.end(), etudiant_recherche, cmp_note);
        if (it != v_etudiants.end()) dummy += it->id;
    }
    t2 = high_resolution_clock::now();
    double t_bin_vec = get_ms(t1, t2);

    t1 = high_resolution_clock::now();
    for (int rep = 0; rep < 1000; ++rep) {
        auto it = lower_bound(l_etudiants.begin(), l_etudiants.end(), etudiant_recherche, cmp_note);
        if (it != l_etudiants.end()) dummy += it->id;
    }
    t2 = high_resolution_clock::now();
    double t_bin_lst = get_ms(t1, t2);

    print_result("4. Recherche dichotomique (1000x)", t_bin_vec, t_bin_lst,
                 "Vector = O(log N) instantane (Random Access) vs List = O(N) degrade (pas d'acces direct)");
}

// ==============================================================================
// 2. CAS D'USAGE RÉEL : HISTORIQUE D'ANNULATION (UNDO/REDO BUFFER DE LOGICIEL)
// ==============================================================================
struct ActionHistorique {
    int id;
    string commande;
    string snapshot;
};

void run_use_case_historique() {
    print_header("CAS D'USAGE 2 : BUFFER D'ANNULATION (UNDO/REDO EN TÊTE DE PILE)");

    const int NB_ACTIONS_INITIALES = 25000;
    const int NB_OPERATIONS_UNDO = 1000;

    vector<ActionHistorique> v_hist;
    list<ActionHistorique> l_hist;

    for (int i = 0; i < NB_ACTIONS_INITIALES; ++i) {
        ActionHistorique act{i, "ACTION_CLIC", "Snapshot_State_Data_XYZ"};
        v_hist.push_back(act);
        l_hist.push_back(act);
    }

    // Annulation fréquente : Retrait en tête de pile (Pop Front / Undo)
    auto t1 = high_resolution_clock::now();
    for (int i = 0; i < NB_OPERATIONS_UNDO; ++i) {
        v_hist.erase(v_hist.begin()); // Déplace 25 000 objets en mémoire à chaque fois !
    }
    auto t2 = high_resolution_clock::now();
    double t_undo_vec = get_ms(t1, t2);

    t1 = high_resolution_clock::now();
    for (int i = 0; i < NB_OPERATIONS_UNDO; ++i) {
        l_hist.pop_front(); // Décroche le premier nœud en O(1)
    }
    t2 = high_resolution_clock::now();
    double t_undo_lst = get_ms(t1, t2);

    print_result("1. Effectuer 1 000 Undo (pop_front)", t_undo_vec, t_undo_lst,
                 "List pop_front est O(1) instantane sans aucun decalage d'objets en memoire");

    // Ajout en tête : nouvel historique enregistré (Push Front)
    t1 = high_resolution_clock::now();
    for (int i = 0; i < NB_OPERATIONS_UNDO; ++i) {
        v_hist.insert(v_hist.begin(), ActionHistorique{999, "NOUVEAU_CLIC", "Data"});
    }
    t2 = high_resolution_clock::now();
    double t_push_front_vec = get_ms(t1, t2);

    t1 = high_resolution_clock::now();
    for (int i = 0; i < NB_OPERATIONS_UNDO; ++i) {
        l_hist.push_front(ActionHistorique{999, "NOUVEAU_CLIC", "Data"});
    }
    t2 = high_resolution_clock::now();
    double t_push_front_lst = get_ms(t1, t2);

    print_result("2. Ajouter 1 000 actions en tete", t_push_front_vec, t_push_front_lst,
                 "List cree un noeud sans deplacer les 24k autres elements existants");
}

// ==============================================================================
// 3. CAS D'USAGE RÉEL : GESTION DE PLAYLIST AUDIO & SPLICE SANS RECOPIE
// ==============================================================================
struct MorceauMusique {
    int id;
    string titre;
    string artiste;
    int dureeSec;
};

void run_use_case_playlist() {
    print_header("CAS D'USAGE 3 : PLAYLIST AUDIO (DEPLACEMENT DE PLAGES D'ÉLÉMENTS)");

    const int NB_MORCEAUX = 40000;
    vector<MorceauMusique> v_play;
    list<MorceauMusique> l_play;

    for (int i = 0; i < NB_MORCEAUX; ++i) {
        MorceauMusique m{i, "Piste_" + to_string(i), "Artiste_" + to_string(i % 100), 210};
        v_play.push_back(m);
        l_play.push_back(m);
    }

    // Réorganisation de playlist : Déplacer un bloc de 100 morceaux du milieu vers le début
    // List dispose de std::list::splice qui échange uniquement les pointeurs sans recopier les objets !
    auto t1 = high_resolution_clock::now();
    // Vector : recopie des éléments, puis suppression de la source, puis insertion au début
    auto v_mid_start = v_play.begin() + 15000;
    auto v_mid_end = v_mid_start + 100;
    vector<MorceauMusique> buffer(v_mid_start, v_mid_end);
    v_play.erase(v_mid_start, v_mid_end);
    v_play.insert(v_play.begin(), buffer.begin(), buffer.end());
    auto t2 = high_resolution_clock::now();
    double t_splice_vec = get_ms(t1, t2);

    t1 = high_resolution_clock::now();
    auto l_mid_start = l_play.begin();
    advance(l_mid_start, 15000);
    auto l_mid_end = l_mid_start;
    advance(l_mid_end, 100);
    // Splice : réassignation immédiate de pointeurs sans allocation ni recopie
    l_play.splice(l_play.begin(), l_play, l_mid_start, l_mid_end);
    t2 = high_resolution_clock::now();
    double t_splice_lst = get_ms(t1, t2);

    print_result("Deplacement de 100 morceaux en tete", t_splice_vec, t_splice_lst,
                 "list::splice commute les pointeurs en O(1) sans copie, sans réallocation ni invalidation");
}

// ==============================================================================
// 4. CAS D'USAGE RÉEL : GESTION DE STOCK E-COMMERCE (PURGE DES ARTICLES ÉPUISÉS)
// ==============================================================================
struct Article {
    int ref;
    string description;
    int quantiteStock;
    double prix;
};

void run_use_case_ecommerce() {
    print_header("CAS D'USAGE 4 : E-COMMERCE (NETTOYAGE DU CATALOGUE / RUPTURES)");

    const int NB_ARTICLES = 100000;
    vector<Article> v_catalogue;
    v_catalogue.reserve(NB_ARTICLES);
    list<Article> l_catalogue;

    mt19937 rng(123);
    uniform_int_distribution<int> distStock(0, 5); // Environ 1/6 des articles sont en rupture (stock == 0)

    for (int i = 0; i < NB_ARTICLES; ++i) {
        Article a{100000 + i, "Produit_" + to_string(i), distStock(rng), 19.99 + (i % 50)};
        v_catalogue.push_back(a);
        l_catalogue.push_back(a);
    }

    // Purge massive de tous les articles avec quantiteStock == 0 (~16 000 suppressions)
    // Vector utilise l'idiome Erase-Remove (std::remove_if compresse le tableau contigu)
    // List utilise list::remove_if (libère chaque nœud individuellement)
    auto t1 = high_resolution_clock::now();
    auto it_remove = remove_if(v_catalogue.begin(), v_catalogue.end(), [](const Article& a) {
        return a.quantiteStock == 0;
    });
    v_catalogue.erase(it_remove, v_catalogue.end());
    auto t2 = high_resolution_clock::now();
    double t_purge_vec = get_ms(t1, t2);

    t1 = high_resolution_clock::now();
    l_catalogue.remove_if([](const Article& a) {
        return a.quantiteStock == 0;
    });
    t2 = high_resolution_clock::now();
    double t_purge_lst = get_ms(t1, t2);

    print_result("Purge 16k articles epuises (Erase)", t_purge_vec, t_purge_lst,
                 "Erase-Remove sur vector compacte la memoire en O(N) sans allocation");
}

// ==============================================================================
// 5. CAS D'USAGE RÉEL : MOTEUR PHYSIQUE / SYSTÈME DE PARTICULES (JEU VIDÉO)
// ==============================================================================
struct Particule {
    float x, y, z;
    float vx, vy, vz;
    float dureeVie;
};

void run_use_case_particules() {
    print_header("CAS D'USAGE 5 : MOTEUR DE JEU (BOUCLE PHYSIQUE 60 FPS / 100k PARTICULES)");

    const int NB_PARTICULES = 100000;
    vector<Particule> v_part(NB_PARTICULES, {0.0f, 0.0f, 0.0f, 1.2f, -0.5f, 0.8f, 10.0f});
    list<Particule> l_part(NB_PARTICULES, {0.0f, 0.0f, 0.0f, 1.2f, -0.5f, 0.8f, 10.0f});

    const float dt = 0.016f; // 1 frame à 60 FPS

    // Simulation de 5 frames successives de mise à jour des positions
    auto t1 = high_resolution_clock::now();
    for (int frame = 0; frame < 5; ++frame) {
        for (auto& p : v_part) {
            p.x += p.vx * dt;
            p.y += p.vy * dt;
            p.z += p.vz * dt;
            p.dureeVie -= dt;
        }
    }
    auto t2 = high_resolution_clock::now();
    double t_sim_vec = get_ms(t1, t2);

    t1 = high_resolution_clock::now();
    for (int frame = 0; frame < 5; ++frame) {
        for (auto& p : l_part) {
            p.x += p.vx * dt;
            p.y += p.vy * dt;
            p.z += p.vz * dt;
            p.dureeVie -= dt;
        }
    }
    t2 = high_resolution_clock::now();
    double t_sim_lst = get_ms(t1, t2);

    print_result("Mise a jour 100k particules (5 frames)", t_sim_vec, t_sim_lst,
                 "Contiguite memoire vector = Auto-Vectorisation CPU (SIMD) et L1 D-Cache");
}

// ==============================================================================
// SYNTHÈSE ARCHITECTURALE & PRISE DE DÉCISION
// ==============================================================================
void afficher_guide_decision() {
    cout << "\n================================================================================\n";
    cout << "  GUIDE DE DÉCISION D'INGÉNIERIE : QUAND CHOISIR VECTOR vs LIST ?\n";
    cout << "================================================================================\n";
    cout << "✔ CHOISIR std::vector DANS 95% DES CAS INDUSTRIELS :\n";
    cout << "  - Traitement en masse (calcul de moyenne, physique, rendu 3D, audio en continu).\n";
    cout << "  - Recherche rapide par predicat ou dichotomie sur donnees triees (std::binary_search).\n";
    cout << "  - Tri frequent (std::sort ultra-rapide grace au Random Access et cache L1/L2).\n";
    cout << "  - Moindre consommation memoire (aucun surcout de pointeurs prev/next de 16 octets/noeud).\n\n";

    cout << "✔ CHOISIR std::list UNIQUEMENT POUR CES CAS SPÉCIFIQUES :\n";
    cout << "  - Buffers avec insertions/retraits constants aux extremites (Historique Undo/Redo).\n";
    cout << "  - Reorganisation de structures lourdes sans copie (std::list::splice pour playlist/LRU Cache).\n";
    cout << "  - Garantie absolue de non-invalidation d'iterateurs ou de references lors d'insertions.\n";
    cout << "================================================================================\n";
}

int main() {
    run_use_case_etudiants();
    run_use_case_historique();
    run_use_case_playlist();
    run_use_case_ecommerce();
    run_use_case_particules();
    afficher_guide_decision();
    return 0;
}
