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

clean:
	rm -rf obj $(LIB) $(PROGS)

.PHONY: all run clean
