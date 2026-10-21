# TP Itérateurs et Conteneurs STL (`std::vector`, `std::list`, `std::deque`)

Ce dépôt contient les travaux pratiques et benchmarks consacrés à l'étude approfondie de `std::vector`, des catégories d'itérateurs et des compromis de performances des conteneurs de la STL en C++.

---

## 📁 Nouvelle Organisation du Projet

Le projet est structuré de manière modulaire en plusieurs répertoires dédiés :

```text
iterators/
├── Makefile                          # Automatisation de la compilation et exécution
├── README.md                         # Documentation du projet
├── src/                              # Fichiers sources C++
│   ├── 01_iterateurs_inverses.cpp
│   ├── 02_inversion_plages.cpp
│   ├── 03_invalidation_iterateurs.cpp
│   ├── 04_benchmark_conteneurs.cpp
│   ├── 05_benchmark_fichier_vector_vs_list.cpp
│   └── 06_use_cases_reels_vector_vs_list.cpp
├── executables/                      # Binaires compilés
│   ├── 01_iterateurs_inverses
│   ├── 02_inversion_plages
│   ├── 03_invalidation_iterateurs
│   ├── 04_benchmark_conteneurs
│   ├── 05_benchmark_fichier_vector_vs_list
│   └── 06_use_cases_reels_vector_vs_list
├── data/                             # Fichiers de données de test et sorties
│   ├── data.txt                      # Fichier d'entrée de 200 000 entiers
│   ├── data_modifie.txt
│   ├── data_vector.txt               # Sortie générée par le benchmark vector
│   └── data_list.txt                 # Sortie générée par le benchmark list
└── documents/                        # Guides et documentation pédagogique
    ├── Guide_Complet_Vector_et_Iterateurs.pdf
    └── generate_guide_pdf.py         # Script Python pour régénérer le PDF
```

---

## 📄 Description des Fichiers Sources (`src/`)

| Fichier Source | Description |
| :--- | :--- |
| **[`01_iterateurs_inverses.cpp`](file:///run/media/zakariae-bakkari/linux/Education/Phase1/Prog_Objet_Avancée_et_Design_Patterns/Assignments/tp/iterators/src/01_iterateurs_inverses.cpp)** | Manipulation des itérateurs constants et conversion vers les itérateurs inverses (`std::reverse_iterator`). |
| **[`02_inversion_plages.cpp`](file:///run/media/zakariae-bakkari/linux/Education/Phase1/Prog_Objet_Avancée_et_Design_Patterns/Assignments/tp/iterators/src/02_inversion_plages.cpp)** | Utilisation de `std::reverse` sur des sous-plages ciblées soit par arithmétique d'itérateurs, soit par recherche de valeurs (`std::find`). |
| **[`03_invalidation_iterateurs.cpp`](file:///run/media/zakariae-bakkari/linux/Education/Phase1/Prog_Objet_Avancée_et_Design_Patterns/Assignments/tp/iterators/src/03_invalidation_iterateurs.cpp)** | Démonstration du piège de l'invalidation d'un itérateur lors d'une insertion provoquant une réallocation mémoire. |
| **[`04_benchmark_conteneurs.cpp`](file:///run/media/zakariae-bakkari/linux/Education/Phase1/Prog_Objet_Avancée_et_Design_Patterns/Assignments/tp/iterators/src/04_benchmark_conteneurs.cpp)** | Comparatif exhaustif des performances de `std::vector`, `std::deque` et `std::list` (push_back, push_front, tri, parcours séquentiel). |
| **[`05_benchmark_fichier_vector_vs_list.cpp`](file:///run/media/zakariae-bakkari/linux/Education/Phase1/Prog_Objet_Avancée_et_Design_Patterns/Assignments/tp/iterators/src/05_benchmark_fichier_vector_vs_list.cpp)** | Benchmark complet mesurant les pires cas (worst-case) sur 200 000 lignes : insertions en tête/milieu, scans sans succès, agrandissement (resize), mises à jour massives et sauvegarde. |
| **[`06_use_cases_reels_vector_vs_list.cpp`](file:///run/media/zakariae-bakkari/linux/Education/Phase1/Prog_Objet_Avancée_et_Design_Patterns/Assignments/tp/iterators/src/06_use_cases_reels_vector_vs_list.cpp)** | Comparatif sur 5 cas d'usage réels : Gestion d'étudiants (recherche, moyennes, tri), historique Undo/Redo, playlist audio (splice sans copie), e-commerce (purge) et moteur physique (100k particules). |

---

## ⚙️ Compilation et Exécution

Un `Makefile` ainsi qu'un lanceur interactif sont disponibles à la racine :

### 🚀 Menu interactif de sélection (Recommandé)
Pour afficher la liste des programmes et choisir directement lequel exécuter :
```bash
make run
# ou
make program
# ou directement
./run.sh
```

---

### Autres cibles Make utiles
```bash
make all        # Compile tous les programmes dans executables/
make run_01     # Exécute 01_iterateurs_inverses directement
make run_04     # Exécute le benchmark conteneurs
make run_05     # Exécute le benchmark sur fichier (200k lignes)
make run_06     # Exécute les cas d'usage réels (Étudiants, Undo, Playlist, etc.)
make clean      # Supprime les exécutables générés
```

---

## 📚 Documentation et Support de Cours

Dans le dossier **[`documents/`](file:///run/media/zakariae-bakkari/linux/Education/Phase1/Prog_Objet_Avancée_et_Design_Patterns/Assignments/tp/iterators/documents)** :
- **[`Guide_Complet_Vector_et_Iterateurs.pdf`](file:///run/media/zakariae-bakkari/linux/Education/Phase1/Prog_Objet_Avancée_et_Design_Patterns/Assignments/tp/iterators/documents/Guide_Complet_Vector_et_Iterateurs.pdf)** : Guide complet illustré sur le fonctionnement interne de `std::vector` (capacité, réallocations, catégories d'itérateurs, localité de cache).
- **[`generate_guide_pdf.py`](file:///run/media/zakariae-bakkari/linux/Education/Phase1/Prog_Objet_Avancée_et_Design_Patterns/Assignments/tp/iterators/documents/generate_guide_pdf.py)** : Script de régénération du document PDF.
