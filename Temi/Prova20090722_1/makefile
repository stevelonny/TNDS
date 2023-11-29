LIBS:=`root-config --libs`
INCS:=`root-config --cflags`
compito: compito.o differenzia.o
	g++ compito.o differenzia.o ${LIBS} ${INCS} -o compito.x
compito.o: differenzia.hpp compito.cpp
	g++ -c compito.cpp ${LIBS} ${INCS} -o compito.o
differenzia.o: differenzia.cpp differenzia.hpp operator.hpp vettoriale.hpp
	g++ -c differenzia.cpp -o differenzia.o
clean:
	rm *.o