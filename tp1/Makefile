CXX      = g++
CXXFLAGS = -Wall -Wextra -O2 -Iinclude
HEADERS  = $(wildcard include/*.h include/*.tpp)
PROGS    = test_pile test_expression test_conversion

# Bibliothèque partagée (équivalent Linux d'une DLL)
LIB      = libpile.so
LIB_OBJS = obj/PileTableau.o obj/PileListe.o obj/Expression.o

all: $(LIB) $(PROGS)

# -fPIC : code indépendant de la position, obligatoire dans une .so
obj/%.o: src/%.cpp $(HEADERS) | obj
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

$(LIB): $(LIB_OBJS)
	$(CXX) -shared -Wl,-soname,$(LIB) $^ -o $@

# Les programmes sont liés à libpile.so ; rpath=$ORIGIN leur permet de
# trouver la bibliothèque dans leur propre dossier (sans LD_LIBRARY_PATH).
%: src/%.cpp $(HEADERS) $(LIB)
	$(CXX) $(CXXFLAGS) $< -L. -lpile -Wl,-rpath,'$$ORIGIN' -o $@

obj:
	mkdir -p obj

run: all
	./test_pile && ./test_expression && ./test_conversion

# ---- Étapes de compilation, un fichier par étape dans compilation/ ----
#   .ii : prétraitement        .s : assembleur       .o : code objet
#   .a  : bibliothèque statique .so : bibliothèque dynamique
#   test_pile / test_pile_statique : exécutables ELF Linux
ETAPES = compilation

etapes: $(ETAPES)/test_pile.ii $(ETAPES)/test_pile.s $(ETAPES)/test_pile.o \
        $(ETAPES)/libpile.a $(ETAPES)/libpile.so \
        $(ETAPES)/test_pile $(ETAPES)/test_pile_statique

# 1. prétraitement : includes recopiés, macros remplacées, commentaires supprimés
$(ETAPES)/%.ii: src/%.cpp $(HEADERS) | $(ETAPES)
	$(CXX) $(CXXFLAGS) -E $< -o $@

# 2. compilation : C++ prétraité -> assembleur x86-64
$(ETAPES)/%.s: $(ETAPES)/%.ii
	$(CXX) $(CXXFLAGS) -S $< -o $@

# 3. assemblage : assembleur -> code objet (non exécutable)
$(ETAPES)/%.o: $(ETAPES)/%.s
	$(CXX) -c $< -o $@

# 4. bibliothèques : archive statique (.a) et bibliothèque partagée (.so)
$(ETAPES)/libpile.a: $(LIB_OBJS) | $(ETAPES)
	ar rcs $@ $^

$(ETAPES)/libpile.so: $(LIB) | $(ETAPES)
	cp $< $@

# 5. édition de liens : dynamique (libpile.so chargée au lancement)
#    et statique (code de libpile.a copié dans l'exécutable)
$(ETAPES)/test_pile: $(ETAPES)/test_pile.o $(ETAPES)/libpile.so
	$(CXX) $< -L$(ETAPES) -lpile -Wl,-rpath,'$$ORIGIN' -o $@

$(ETAPES)/test_pile_statique: $(ETAPES)/test_pile.o $(ETAPES)/libpile.a
	$(CXX) $^ -o $@

$(ETAPES):
	mkdir -p $(ETAPES)

clean:
	rm -rf obj $(LIB) $(PROGS) $(ETAPES)

.PHONY: all run etapes clean
