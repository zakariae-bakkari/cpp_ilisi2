#!/usr/bin/env bash

# Couleurs pour un affichage soigné
CYAN='\033[0;36m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
RED='\033[0;31m'
BOLD='\033[1m'
NC='\033[0m' # No Color

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$ROOT_DIR" || exit 1

while true; do
    clear
    echo -e "${BLUE}${BOLD}======================================================================${NC}"
    echo -e "${BLUE}${BOLD}   Prog Objet Avancée et Design Patterns - Lanceur Principal de TP   ${NC}"
    echo -e "${BLUE}${BOLD}======================================================================${NC}"
    echo -e " ${GREEN}1)${NC} ${BOLD}Exercice 1${NC} : Pile Générique, DDL & Expressions"
    echo -e " ${GREEN}2)${NC} ${BOLD}Exercice 2${NC} : Recherche d'une sous-chaîne (lib dynamique)"
    echo -e " ${GREEN}3)${NC} ${BOLD}Exercice 3${NC} : Recherche de sous-chaîne dans des fichiers"
    echo -e " ${GREEN}4)${NC} ${BOLD}Exercice 4${NC} : Remplacement d'une sous-chaîne dans un fichier"
    echo -e " ${GREEN}5)${NC} ${BOLD}Exercice 5${NC} : Plus Grande Sous-Chaîne (mot le plus long)"
    echo -e " ${GREEN}6)${NC} ${BOLD}Iterators${NC}  : Itérateurs STL & Benchmarks (Vector vs Deque vs List)"
    echo -e " ${RED}q)${NC} ${BOLD}Quitter${NC}"
    echo -e "${BLUE}----------------------------------------------------------------------${NC}"
    read -rp " Choisissez le TP à exécuter [1-6 ou q] : " tp_choice

    case "$tp_choice" in
        1)
            bash "$ROOT_DIR/exercice 1 (pile generque,ddl)/run.sh"
            ;;
        2)
            bash "$ROOT_DIR/exercice 2 (Recherche d'une sous chaine)/run.sh"
            ;;
        3)
            bash "$ROOT_DIR/exercice 3 (Recherche d'une sous chaine depuis des fichers)/run.sh"
            ;;
        4)
            bash "$ROOT_DIR/exercice 4 (Remplacer Sous chaine par un autre)/run.sh"
            ;;
        5)
            bash "$ROOT_DIR/exercice 5 (Plus Grand Sous Chaine)/run.sh"
            ;;
        6)
            bash "$ROOT_DIR/iterators/run.sh"
            ;;
        q|Q)
            echo -e "\n${GREEN}Au revoir !${NC}\n"
            exit 0
            ;;
        *)
            echo -e "\n${RED}Option invalide !${NC}"
            sleep 1
            ;;
    esac
done
