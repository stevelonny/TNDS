compito: main.o integratore.o funzioni.o montecarlo.o random.o
	g++ main.o integratore.o funzioni.o montecarlo.o random.o ../format.cc -o main.x
main.o: funzioni.hpp integratore.hpp montecarlo.hpp main.cpp
	g++ -c main.cpp -o main.o
integratore.o : funzioni.hpp integratore.hpp integratore.cpp
	g++ -c integratore.cpp -o integratore.o
random.o : random.cpp random.hpp
	g++ -c random.cpp -o random.o
funzioni.o : funzioni.hpp funzioni.cpp
	g++ -c funzioni.cpp -o funzioni.o
montecarlo.o: funzioni.hpp random.hpp montecarlo.hpp montecarlo.cpp
	g++ -c montecarlo.cpp -o montecarlo.o
clean:
	rm *.o