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
if [ ! -f "prog" ] || [ "recherche_fichier.cpp" -nt "prog" ]; then
    echo -e "${YELLOW}Compilation de recherche_fichier.cpp...${NC}"
    g++ -O2 -Wall recherche_fichier.cpp -o prog
fi

while true; do
    echo -e "\n${CYAN}${BOLD}======================================================================${NC}"
    echo -e "${CYAN}${BOLD}   Exercice 3 : Recherche d'une sous-chaîne depuis des fichiers       ${NC}"
    echo -e "${CYAN}${BOLD}======================================================================${NC}"
    echo -e " ${GREEN}1)${NC} ${BOLD}Lancer le programme ./prog${NC}"
    echo -e " ${RED}q)${NC} ${BOLD}Retour / Quitter${NC}"
    echo -e "${CYAN}----------------------------------------------------------------------${NC}"
    read -rp " Entrez votre choix [1 ou q] : " choice

    case "$choice" in
        1)
            echo -e "\n${YELLOW}>>> Exécution de ./prog :${NC}\n"
            ./prog
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
