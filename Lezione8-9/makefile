LIBS:=`root-config --libs`
INCS:=`root-config --cflags`
riproviamo: riproviamo.o
	g++ riproviamo.o differenzia.o vettoriale.o ../format.cc -o riproviamo.x
forzato: forzato.o
	g++ forzato.o differenzia.o vettoriale.o ../format.cc -o forzato.x
graphforzato: graphforzato.o
	g++ graphforzato.o differenzia.o vettoriale.o ${LIBS} ${INCS} -o graphforzato.x
pendolo: pendolo.o
	g++ pendolo.o differenzia.o vettoriale.o ${LIBS} ${INCS} -o pendolo.x
graphkutta: graphkutta.o
	g++ graphkutta.o differenzia.o vettoriale.o ${LIBS} ${INCS} -o graphkutta.x 
error: error.o
	g++ error.o differenzia.o vettoriale.o ${LIBS} ${INCS} -o error.x 
graph: graph.o
	g++ graph.o differenzia.o vettoriale.o ${LIBS} ${INCS} -o graph.x 
riproviamo.o: differenzia.o vettoriale.o
	g++ -c riproviamo.cpp -o riproviamo.o
forzato.o: differenzia.o vettoriale.o
	g++ -c forzato.cpp -o forzato.o
graphforzato.o: differenzia.o vettoriale.o
	g++ -c graphforzato.cpp ${LIBS} ${INCS} -o graphforzato.o
pendolo.o: differenzia.o vettoriale.o
	g++ -c pendolo.cpp ${LIBS} ${INCS} -o pendolo.o
error.o: differenzia.o vettoriale.o
	g++ -c error.cpp ${LIBS} ${INCS} -o error.o
graphkutta.o: differenzia.o vettoriale.o
	g++ -c graphkutta.cpp ${LIBS} ${INCS} -o graphkutta.o
graph.o: differenzia.o vettoriale.o
	g++ -c graph.cpp ${LIBS} ${INCS} -o graph.o
differenzia.o: differenzia.cpp differenzia.hpp vettoriale.o
	g++ -c differenzia.cpp -o differenzia.o
vettoriale.o: vettoriale.cpp vettoriale.hpp operator.hpp
	g++ -c vettoriale.cpp -o vettoriale.o
clean:
	rm *.o