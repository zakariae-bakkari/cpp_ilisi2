#!/usr/bin/env bash

CYAN='\033[0;36m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
BOLD='\033[1m'
NC='\033[0m'

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR" || exit 1

# Compilation
if [ ! -f "plus_long_mot" ] || [ "plus_long_mot.cpp" -nt "plus_long_mot" ]; then
    echo -e "${YELLOW}Compilation de plus_long_mot.cpp...${NC}"
    g++ -O2 -Wall plus_long_mot.cpp -o plus_long_mot
fi

while true; do
    echo -e "\n${CYAN}${BOLD}======================================================================${NC}"
    echo -e "${CYAN}${BOLD}       Exercice 5 : Plus Grande Sous-Chaîne                           ${NC}"
    echo -e "${CYAN}${BOLD}======================================================================${NC}"
    echo -e " ${GREEN}1)${NC} ${BOLD}Lancer le programme ./plus_long_mot${NC}"
    echo -e " ${RED}q)${NC} ${BOLD}Retour / Quitter${NC}"
    echo -e "${CYAN}----------------------------------------------------------------------${NC}"
    read -rp " Entrez votre choix [1 ou q] : " choice

    case "$choice" in
        1)
            echo -e "\n${YELLOW}>>> Exécution de ./plus_long_mot :${NC}\n"
            ./plus_long_mot
            ;;
        q|Q)
            break
            ;;
        *)
            echo -e "\n${RED}Option invalide !${NC}"
            ;;
    esac

    echo ""
    read -rp "Appuyez sur [Entrée] pour continuer..." dummy
done
