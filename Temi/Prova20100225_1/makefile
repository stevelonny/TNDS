compito: compito.o differenzia.o vettoriale.o
	g++ compito.o differenzia.o vettoriale.o ../format.cc -o compito.x
compito.o: compito.cpp differenzia.hpp vettoriale.hpp
	g++ -c compito.cpp -o compito.o
differenzia.o: differenzia.cpp differenzia.hpp vettoriale.hpp
	g++ -c differenzia.cpp -o differenzia.o
vettoriale.o: vettoriale.cpp vettoriale.hpp operator.hpp
	g++ -c vettoriale.cpp -o vettoriale.o
clean:
	rm *.o