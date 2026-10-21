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
if [ ! -f "rempl" ] || [ "remplacement.cpp" -nt "rempl" ]; then
    echo -e "${YELLOW}Compilation de remplacement.cpp...${NC}"
    g++ -O2 -Wall remplacement.cpp -o rempl
fi

while true; do
    echo -e "\n${CYAN}${BOLD}======================================================================${NC}"
    echo -e "${CYAN}${BOLD}       Exercice 4 : Remplacer une sous-chaîne dans un fichier         ${NC}"
    echo -e "${CYAN}${BOLD}======================================================================${NC}"
    echo -e " ${GREEN}1)${NC} ${BOLD}Lancer le programme ./rempl${NC}"
    echo -e " ${RED}q)${NC} ${BOLD}Retour / Quitter${NC}"
    echo -e "${CYAN}----------------------------------------------------------------------${NC}"
    read -rp " Entrez votre choix [1 ou q] : " choice

    case "$choice" in
        1)
            echo -e "\n${YELLOW}>>> Exécution de ./rempl :${NC}\n"
            ./rempl
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
