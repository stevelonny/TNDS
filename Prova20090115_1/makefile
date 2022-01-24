compito: compito.o funzioni.o integratore.o ../format.cc
	g++ compito.o integratore.o funzioni.o ../format.cc -o compito.x
compito.o: funzioni.hpp integratore.hpp compito.cpp ../fmtlib.h
	g++ -c compito.cpp -o compito.o
integratore.o: funzioni.hpp integratore.cpp integratore.hpp
	g++ -c integratore.cpp -o integratore.o
funzioni.o: funzioni.cpp funzioni.hpp
	g++ -c funzioni.cpp -o funzioni.o
clean:
	rm *.o