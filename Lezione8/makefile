LIBS:=`root-config --libs`
INCS:=`root-config --cflags`
error: error.o
	g++ error.o differenzia.o vettoriale.o ${LIBS} ${INCS} -o error.x 
graph: graph.o
	g++ graph.o differenzia.o vettoriale.o ${LIBS} ${INCS} -o graph.x 
error.o: differenzia.o vettoriale.o
	g++ -c error.cpp ${LIBS} ${INCS} -o error.o
graph.o: differenzia.o vettoriale.o
	g++ -c graph.cpp ${LIBS} ${INCS} -o graph.o
differenzia.o: differenzia.cpp differenzia.hpp vettoriale.o
	g++ -c differenzia.cpp -o differenzia.o
vettoriale.o: vettoriale.cpp vettoriale.hpp operator.hpp
	g++ -c vettoriale.cpp -o vettoriale.o
clean:
	rm *.o