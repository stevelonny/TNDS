esercizio7.2 : funzioni.o integratore.o fmtlib.h esercizio7.2.o format.cc
	g++ funzioni.o integratore.o esercizio7.2.o format.cc -o esercizio7.2.x
esercizio7.0 : funzioni.o integratore.o fmtlib.h esercizio7.0.o format.cc
	g++ funzioni.o integratore.o esercizio7.0.o format.cc -o esercizio7.0.x
esercizio7.2.o : funzioni.hpp integratore.hpp fmtlib.h esercizio7.2.cpp
	g++ -c esercizio7.2.cpp -o esercizio7.2.o
esercizio7.0.o : funzioni.hpp integratore.hpp fmtlib.h esercizio7.0.cpp
	g++ -c esercizio7.0.cpp -o esercizio7.0.o
integratore.o : funzioni.hpp integratore.hpp integratore.cpp
	g++ -c integratore.cpp -o integratore.o
funzioni.o : funzioni.hpp funzioni.cpp
	g++ -c funzioni.cpp -o funzioni.o
clean :
	rm *.o
