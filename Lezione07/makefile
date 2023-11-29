LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

esercizio7.2 : funzioni.o integratore.o fmtlib.h esercizio7.2.o 
	g++ funzioni.o integratore.o esercizio7.2.o  -o esercizio7.2.x
esercizio7.1 : funzioni.o integratore.o fmtlib.h esercizio7.1.o  esercizio7.1.cpp
	g++ funzioni.o integratore.o esercizio7.1.o  ${LIBS} ${INCS} -o esercizio7.1.x
esercizio7.1.o : funzioni.o integratore.o fmtlib.h esercizio7.0.o 
	g++ -c esercizio7.1.cpp ${LIBS} ${INCS} -o esercizio7.1.o
esercizio7.0 : funzioni.o integratore.o fmtlib.h esercizio7.0.o 
	g++ funzioni.o integratore.o esercizio7.0.o  -o esercizio7.0.x
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
