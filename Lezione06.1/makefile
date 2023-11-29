sium : sium.o funzioni.o solutore.o
	g++ sium.o funzioni.o solutore.o  -o sium.x
tansecvsbis : tansecvsbis.o funzioni.o solutore.o
	g++ tansecvsbis.o funzioni.o solutore.o  -o tansecvsbis.x
esercizio6.3 : esercizio6.3.o funzioni.o solutore.o
	g++ esercizio6.3.o funzioni.o solutore.o -o esercizio6.3.x
sium.o : funzioni.hpp solutore.hpp sium.cpp
	g++ -c sium.cpp -o sium.o
tansecvsbis.o : funzioni.hpp solutore.hpp tansecvsbis.cpp
	g++ -c tansecvsbis.cpp -o tansecvsbis.o
esercizio6.3.o : funzioni.hpp solutore.hpp esercizio6.3.cpp
	g++ -c esercizio6.3.cpp -o esercizio6.3.o
solutore.o : funzioni.hpp solutore.hpp solutore.cpp
	g++ -c solutore.cpp -o solutore.o
funzioni.o : funzioni.hpp funzioni.cpp
	g++ -c funzioni.cpp -o funzioni.o
clean : 
	rm *.o