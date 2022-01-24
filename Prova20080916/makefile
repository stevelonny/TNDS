LIBS:=`root-config --libs`
INCS:=`root-config --cflags`
compito: compito.o differenzia.o vettoriale.o
	g++ compito.o differenzia.o vettoriale.o ../format.cc ${LIBS} ${INCS} -o compito.x
compito.o: differenzia.hpp vettoriale.hpp compito.cpp
	g++ -c compito.cpp ${LIBS} ${INCS} -o compito.o
differenzia.o: differenzia.cpp differenzia.hpp vettoriale.o
	g++ -c differenzia.cpp -o differenzia.o
vettoriale.o: vettoriale.cpp vettoriale.hpp operator.hpp
	g++ -c vettoriale.cpp -o vettoriale.o
clean:
	rm *.o