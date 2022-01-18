main: vettore.o stats.o main.o
	g++ main.o stats.o vettore.o -o main
main.o: main.cpp vettore.h stats.h
	g++ -c main.cpp -o main.o
stats.o: stats.h stats.cpp vettore.h
	g++ -c stats.cpp -o stats.o
vettore.o: vettore.h vettore.cpp
	g++ -c vettore.cpp -o vettore.o