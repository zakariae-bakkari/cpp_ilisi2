#!/usr/bin/env bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR" || exit 1

# Couleurs pour un affichage soigné
CYAN='\033[0;36m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
BOLD='\033[1m'
NC='\033[0m' # No Color

# Compilation préalable si nécessaire
make -s all

while true; do
    clear
    echo -e "${CYAN}${BOLD}======================================================================${NC}"
    echo -e "${CYAN}${BOLD}       TP C++ : Itérateurs et Conteneurs STL - Menu Interactif        ${NC}"
    echo -e "${CYAN}${BOLD}======================================================================${NC}"
    echo -e " ${GREEN}1)${NC} ${BOLD}01_iterateurs_inverses${NC}          : Itérateurs constants & reverse_iterator"
    echo -e " ${GREEN}2)${NC} ${BOLD}02_inversion_plages${NC}             : Inversion par indices et valeurs (std::reverse)"
    echo -e " ${GREEN}3)${NC} ${BOLD}03_invalidation_iterateurs${NC}      : Piège d'invalidation après insertion"
    echo -e " ${GREEN}4)${NC} ${BOLD}04_benchmark_conteneurs${NC}         : Benchmark comparatif Vector vs Deque vs List"
    echo -e " ${GREEN}5)${NC} ${BOLD}05_benchmark_fichier_vector_vs_list${NC} : Benchmark Worst-case sur fichier (200k lignes)"
    echo -e " ${GREEN}6)${NC} ${BOLD}06_use_cases_reels_vector_vs_list${NC}   : Cas d'usage réels (Étudiants, Undo/Redo, Playlist, E-commerce, Physique)"
    echo -e " ${GREEN}7)${NC} ${BOLD}07_arbre_BFS${NC}                        : Parcours en largeur (BFS) d'un arbre"
    echo -e " ${GREEN}8)${NC} ${BOLD}08_benchmark_recherche_vector_list_pile${NC} : Recherche début/milieu/fin (vector vs list vs pile)"
    echo -e " ${GREEN}10)${NC} ${BOLD}09_arbre_binaire_recherche${NC}         : Arbre binaire de recherche (insertion + recherche)"
    echo -e " ${YELLOW}9)${NC} ${BOLD}Exécuter tous les benchmarks${NC}    : Lance les benchmarks 04, 05, 06 et 08 à la suite"
    echo -e " ${RED}q)${NC} ${BOLD}Quitter${NC}"
    echo -e "${CYAN}----------------------------------------------------------------------${NC}"
    read -rp " Entrez votre choix [1-10 ou q] : " choice

    case "$choice" in
        1)
            echo -e "\n${YELLOW}>>> Exécution de 01_iterateurs_inverses :${NC}\n"
            ./executables/01_iterateurs_inverses
            ;;
        2)
            echo -e "\n${YELLOW}>>> Exécution de 02_inversion_plages :${NC}\n"
            ./executables/02_inversion_plages
            ;;
        3)
            echo -e "\n${YELLOW}>>> Exécution de 03_invalidation_iterateurs :${NC}\n"
            ./executables/03_invalidation_iterateurs
            echo ""
            ;;
        4)
            echo -e "\n${YELLOW}>>> Exécution de 04_benchmark_conteneurs :${NC}\n"
            ./executables/04_benchmark_conteneurs
            ;;
        5)
            echo -e "\n${YELLOW}>>> Exécution de 05_benchmark_fichier_vector_vs_list :${NC}\n"
            ./executables/05_benchmark_fichier_vector_vs_list
            ;;
        6)
            echo -e "\n${YELLOW}>>> Exécution de 06_use_cases_reels_vector_vs_list :${NC}\n"
            ./executables/06_use_cases_reels_vector_vs_list
            ;;
        7)
            echo -e "\n${YELLOW}>>> Exécution de 07_arbre_BFS :${NC}\n"
            ./executables/07_arbre_BFS
            ;;
        8)
            echo -e "\n${YELLOW}>>> Exécution de 08_benchmark_recherche_vector_list_pile :${NC}\n"
            ./executables/08_benchmark_recherche_vector_list_pile
            ;;
        9)
            echo -e "\n${YELLOW}>>> Exécution de 04_benchmark_conteneurs :${NC}\n"
            ./executables/04_benchmark_conteneurs
            echo -e "\n${YELLOW}>>> Exécution de 05_benchmark_fichier_vector_vs_list :${NC}\n"
            ./executables/05_benchmark_fichier_vector_vs_list
            echo -e "\n${YELLOW}>>> Exécution de 06_use_cases_reels_vector_vs_list :${NC}\n"
            ./executables/06_use_cases_reels_vector_vs_list
            echo -e "\n${YELLOW}>>> Exécution de 08_benchmark_recherche_vector_list_pile :${NC}\n"
            ./executables/08_benchmark_recherche_vector_list_pile
            ;;
        10)
            echo -e "\n${YELLOW}>>> Exécution de 09_arbre_binaire_recherche :${NC}\n"
            ./executables/09_arbre_binaire_recherche
            ;;
        q|Q)
            echo -e "\n${GREEN}Au revoir !${NC}\n"
            exit 0
            ;;
        *)
            echo -e "\n${RED}Option invalide !${NC}"
            ;;
    esac

    echo ""
    read -rp "Appuyez sur [Entrée] pour revenir au menu..." dummy
done
