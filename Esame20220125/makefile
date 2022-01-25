LIBS:=`root-config --libs`
INCS:=`root-config --cflags`
compito : compito.o solutore.o funzioni.o integratore.o montecarlo.o random.o format.cc fmtlib.h
	g++ compito.o solutore.o funzioni.o integratore.o montecarlo.o random.o format.cc ${LIBS} ${INCS} -o compito.x
compito.o :	funzioni.hpp solutore.hpp compito.cpp fmtlib.h
	g++ -c compito.cpp ${LIBS} ${INCS} -o compito.o
integratore.o : funzioni.hpp integratore.hpp integratore.cpp
	g++ -c integratore.cpp -o integratore.o
solutore.o : funzioni.hpp solutore.hpp solutore.cpp
	g++ -c solutore.cpp -o solutore.o
funzioni.o : funzioni.hpp funzioni.cpp
	g++ -c funzioni.cpp -o funzioni.o
random.o : random.cpp random.hpp
	g++ -c random.cpp -o random.o
montecarlo.o: funzioni.hpp random.hpp montecarlo.hpp montecarlo.cpp
	g++ -c montecarlo.cpp -o montecarlo.o
clean : 
	rm *.o