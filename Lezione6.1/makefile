sium : sium.o funzioni.o solutore.o
	g++ sium.o funzioni.o solutore.o format.cc -o sium.x
tansecvsbis : tansecvsbis.o funzioni.o solutore.o
	g++ tansecvsbis.o funzioni.o solutore.o format.cc -o tansecvsbis.x
provasecante : provasecante.o funzioni.o solutore.o
	g++ provasecante.o funzioni.o solutore.o -o provasecante.x
esercizio6.3 : esercizio6.3.o funzioni.o solutore.o
	g++ esercizio6.3.o funzioni.o solutore.o -o esercizio6.3.x
esercizio6.2 : esercizio6.2.o funzioni.o solutore.o
	g++ esercizio6.2.o funzioni.o solutore.o -o esercizio6.2.x
esercizio6.1 : esercizio6.1.o funzioni.o
	g++ esercizio6.1.o funzioni.o -o esercizio6.1.x
esercizio6.0 : esercizio6.0.o particella.o
	g++ esercizio6.0.o particella.o -o esercizio6.0.x
sium.o : funzioni.hpp solutore.hpp sium.cpp
	g++ -c sium.cpp -o sium.o
tansecvsbis.o : funzioni.hpp solutore.hpp tansecvsbis.cpp
	g++ -c tansecvsbis.cpp -o tansecvsbis.o
provasecante.o : funzioni.hpp solutore.hpp provasecante.cpp
	g++ -c provasecante.cpp -o provasecante.o
esercizio6.3.o : funzioni.hpp solutore.hpp esercizio6.3.cpp
	g++ -c esercizio6.3.cpp -o esercizio6.3.o
esercizio6.2.o : funzioni.hpp solutore.hpp esercizio6.2.cpp
	g++ -c esercizio6.2.cpp -o esercizio6.2.o
esercizio6.1.o : funzioni.hpp esercizio6.1.cpp
	g++ -c esercizio6.1.cpp -o esercizio6.1.o
esercizio6.0.o : particella.hpp esercizio6.0.cpp
	g++ -c esercizio6.0.cpp -o esercizio6.0.o
solutore.o : funzioni.hpp solutore.hpp solutore.cpp
	g++ -c solutore.cpp -o solutore.o
funzioni.o : funzioni.hpp funzioni.cpp
	g++ -c funzioni.cpp -o funzioni.o
particella.o : particella.hpp particella.cpp
	g++ -c particella.cpp -o particella.o
clean : 
	rm *.o