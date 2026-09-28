# Génère séparément chaque étape de la compilation de programme.cpp.
#   make          -> toutes les étapes
#   make clean && make DEBUG=1  -> idem avec la macro DEBUG définie
#   make clean    -> supprime les fichiers générés

CXX      = g++
CXXFLAGS = -Wall -Wextra -I../include
ifdef DEBUG
CXXFLAGS += -DDEBUG
endif

SRC = programme.cpp
LIB = ../libpile.so

all: 1_pretraitement/programme.ii \
     1_pretraitement/programme_sans_includes.ii \
     2_compilation/programme.s \
     3_assemblage/programme.o \
     3_assemblage/symboles.txt \
     4_edition_liens/programme \
     4_edition_liens/ldd.txt

# 1. Prétraitement : includes recopiés, macros remplacées,
#    commentaires supprimés, #ifdef évalués.
1_pretraitement/programme.ii: $(SRC)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -E $< -o $@

# Même étape en ne gardant que les lignes issues de programme.cpp
# (le fichier complet contient des dizaines de milliers de lignes d'iostream).
1_pretraitement/programme_sans_includes.ii: 1_pretraitement/programme.ii
	awk '/^# [0-9]+ "/ { garder = ($$3 == "\"$(SRC)\"") ; next } garder' $< | cat -s > $@

# 2. Compilation : code C++ prétraité -> assembleur x86-64
2_compilation/programme.s: 1_pretraitement/programme.ii
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -S $< -o $@

# 3. Assemblage : assembleur -> code objet (binaire, non exécutable)
3_assemblage/programme.o: 2_compilation/programme.s
	mkdir -p $(@D)
	$(CXX) -c $< -o $@

# Symboles du .o : "U" = non défini ici, à résoudre à l'édition de liens
3_assemblage/symboles.txt: 3_assemblage/programme.o
	nm -C $< > $@

# 4. Édition de liens : programme.o + libpile.so + bibliothèque C++ -> exécutable
4_edition_liens/programme: 3_assemblage/programme.o $(LIB)
	mkdir -p $(@D)
	$(CXX) $< -L.. -lpile -Wl,-rpath,'$$ORIGIN/../..' -o $@

# Bibliothèques partagées chargées au lancement
4_edition_liens/ldd.txt: 4_edition_liens/programme
	ldd $< > $@

$(LIB):
	$(MAKE) -C .. libpile.so

run: all
	./4_edition_liens/programme

clean:
	rm -rf 1_pretraitement 2_compilation 3_assemblage 4_edition_liens

.PHONY: all run clean
