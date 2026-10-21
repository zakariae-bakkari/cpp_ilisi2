# 💻 Programmation Objet Avancée et Design Patterns en C++

Ce dépôt regroupe l'ensemble des Travaux Pratiques (TP), exercices et benchmarks réalisés dans le cadre du module **Programmation Objet Avancée et Design Patterns (ILISI 2)**.

---

## 📂 Structure du Répertoire

```text
.
├── run.sh                                                      # Lanceur interactif principal
├── default.conf                                                # Fichier de configuration
├── exercice 1 (pile generque,ddl)/                             # Pile générique, templates & bibliothèques partagées
├── exercice 2 (Recherche d'une sous chaine)/                   # Algorithme de recherche & création de bibliothèques (.so)
├── exercice 3 (Recherche d'une sous chaine depuis des fichers)/ # Analyse et recherche sur fichiers texte volumineux
├── exercice 4 (Remplacer Sous chaine par un autre)/            # Remplacement textuel efficace en flux
├── exercice 5 (Plus Grand Sous Chaine)/                        # Algorithme du mot le plus long / sous-chaîne commune
├── exercice 6 (8-Reines)/                                      # Problème classique des 8 reines (Backtracking)
├── exercice 7 (N-Reines)/                                      # Généralisation aux N-reines
├── exercice 8 (Algo Knuth)/                                    # Algorithme X de Knuth (Dancing Links)
└── iterators/                                                  # Itérateurs STL, Arbres (BFS/DFS) et Benchmarks
    ├── Makefile                                                # Compilation modulaire
    ├── README.md                                               # Documentation détaillée des itérateurs
    ├── src/                                                    # Codes sources C++
    │   ├── 01_iterateurs_inverses.cpp
    │   ├── 02_inversion_plages.cpp
    │   ├── 03_invalidation_iterateurs.cpp
    │   ├── 04_benchmark_conteneurs.cpp
    │   ├── 05_benchmark_fichier_vector_vs_list.cpp
    │   ├── 06_use_cases_reels_vector_vs_list.cpp
    │   └── 07_arbre_BFS.cpp
    ├── data/                                                   # Données d'entrée (200k lignes)
    └── documents/                                              # Guides pédagogiques et PDF
```

---

## 🚀 Utilisation et Exécution

Un lanceur global interactif en bash permet d'accéder et d'exécuter n'importe quel exercice :

```bash
./run.sh
```

### Pour exécuter directement le TP Itérateurs :
```bash
cd iterators
make run
```
