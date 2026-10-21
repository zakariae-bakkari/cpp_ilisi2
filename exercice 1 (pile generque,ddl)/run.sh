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
echo -e "${YELLOW}Compilation en cours...${NC}"
make -s all

while true; do
    echo -e "\n${CYAN}${BOLD}======================================================================${NC}"
    echo -e "${CYAN}${BOLD}       Exercice 1 : Pile Générique & Bibliothèque Dynamique (DDL)     ${NC}"
    echo -e "${CYAN}${BOLD}======================================================================${NC}"
    echo -e " ${GREEN}1)${NC} ${BOLD}test_pile${NC}        : Tests unitaires de la pile générique"
    echo -e " ${GREEN}2)${NC} ${BOLD}test_expression${NC}  : Évaluation et validation d'expressions parenthésées"
    echo -e " ${GREEN}3)${NC} ${BOLD}test_conversion${NC}  : Conversion Infixe vers Postfixe (Notation Polonaise)"
    echo -e " ${YELLOW}4)${NC} ${BOLD}Tout exécuter${NC}    : Lance les 3 programmes à la suite"
    echo -e " ${RED}q)${NC} ${BOLD}Retour / Quitter${NC}"
    echo -e "${CYAN}----------------------------------------------------------------------${NC}"
    read -rp " Entrez votre choix [1-4 ou q] : " choice

    case "$choice" in
        1)
            echo -e "\n${YELLOW}>>> Exécution de ./test_pile :${NC}\n"
            ./test_pile
            ;;
        2)
            echo -e "\n${YELLOW}>>> Exécution de ./test_expression :${NC}\n"
            ./test_expression
            ;;
        3)
            echo -e "\n${YELLOW}>>> Exécution de ./test_conversion :${NC}\n"
            ./test_conversion
            ;;
        4)
            echo -e "\n${YELLOW}>>> Exécution de ./test_pile :${NC}\n"
            ./test_pile
            echo -e "\n${YELLOW}>>> Exécution de ./test_expression :${NC}\n"
            ./test_expression
            echo -e "\n${YELLOW}>>> Exécution de ./test_conversion :${NC}\n"
            ./test_conversion
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
