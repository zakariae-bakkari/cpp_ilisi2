CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O3

SRC_DIR = src
BIN_DIR = executables
DATA_DIR = data
DOC_DIR = documents

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
BINS = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%, $(SRCS))

.PHONY: all clean run program programe menu run_benchmarks help

# Cible par defaut : compilation
all: $(BIN_DIR) $(BINS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/%: $(SRC_DIR)/%.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Menu interactif de selection
run program programe menu: all
	@./run.sh

clean:
	rm -rf $(BIN_DIR)/*

run_01: $(BIN_DIR)/01_iterateurs_inverses
	./$(BIN_DIR)/01_iterateurs_inverses

run_02: $(BIN_DIR)/02_inversion_plages
	./$(BIN_DIR)/02_inversion_plages

run_03: $(BIN_DIR)/03_invalidation_iterateurs
	./$(BIN_DIR)/03_invalidation_iterateurs

run_04: $(BIN_DIR)/04_benchmark_conteneurs
	./$(BIN_DIR)/04_benchmark_conteneurs

run_05: $(BIN_DIR)/05_benchmark_fichier_vector_vs_list
	./$(BIN_DIR)/05_benchmark_fichier_vector_vs_list

run_06: $(BIN_DIR)/06_use_cases_reels_vector_vs_list
	./$(BIN_DIR)/06_use_cases_reels_vector_vs_list

run_07: $(BIN_DIR)/07_arbre_BFS
	./$(BIN_DIR)/07_arbre_BFS

run_08: $(BIN_DIR)/08_benchmark_recherche_vector_list_pile
	./$(BIN_DIR)/08_benchmark_recherche_vector_list_pile

run_09: $(BIN_DIR)/09_arbre_binaire_recherche
	./$(BIN_DIR)/09_arbre_binaire_recherche

run_benchmarks: run_04 run_05 run_06 run_08

help:
	@echo "Cibles disponibles dans ce Makefile :"
	@echo "  make run (ou make program) : Affiche la liste interactive pour choisir et executer un programme"
	@echo "  make all                   : Compile tous les fichiers source dans $(BIN_DIR)/"
	@echo "  make clean                 : Supprime les executables compiles"
	@echo "  make run_01 ... run_09     : Execute directement un programme precis"
	@echo "  make run_benchmarks        : Execute les benchmarks 04, 05, 06 et 08"
