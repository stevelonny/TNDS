LIBS:=`root-config --libs`
INCS:=`root-config --cflags`
compito: compito.o differenzia.o vettoriale.o random.o stats.hpp
	g++ compito.o differenzia.o vettoriale.o random.o ${LIBS} ${INCS} -o compito.x
compito.o: differenzia.hpp vettoriale.hpp random.hpp compito.cpp
	g++ -c compito.cpp ${LIBS} ${INCS} -o compito.o
differenzia.o: differenzia.cpp differenzia.hpp vettoriale.o
	g++ -c differenzia.cpp -o differenzia.o
vettoriale.o: vettoriale.cpp vettoriale.hpp operator.hpp
	g++ -c vettoriale.cpp -o vettoriale.o
random.o: random.hpp random.cpp
	g++ -c random.cpp -o random.o
clean:
	rm *.o