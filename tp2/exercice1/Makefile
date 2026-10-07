CXX = g++
CXXFLAGS = -Wall

all: librecherche.so main

# la librairie dynamique
recherche.o: recherche.cpp recherche.h
	$(CXX) $(CXXFLAGS) -fPIC -c recherche.cpp -o recherche.o

librecherche.so: recherche.o
	$(CXX) -shared recherche.o -o librecherche.so

# le programme qui utilise la librairie
main: main.cpp recherche.h librecherche.so
	$(CXX) $(CXXFLAGS) main.cpp -L. -lrecherche -Wl,-rpath,'$$ORIGIN' -o main

run: all
	./main

clean:
	rm -f recherche.o librecherche.so main
