LIBS:=`root-config --libs`
INCS:=`root-config --cflags`
#Eseguibili
dipolo : dipolo.o posizione.o particella.o puntomateriale.o campovettoriale.o
	g++ dipolo.o puntomateriale.o campovettoriale.o particella.o posizione.o ${LIBS} ${INCS} -o dipolo.x
esercizio2 : esercizio2.o particella.o
	g++ esercizio2.o particella.o -o esercizio2.x
esercizio1 : esercizio1.o posizione.o
	g++ esercizio1.o posizione.o -o esercizio1.x
#File oggetto dei main
dipolo.o : particella.hpp posizione.hpp campovettoriale.hpp puntomateriale.hpp
	g++ -c dipolo.cpp ${LIBS} ${INCS} -o dipolo.o
esercizio1.o : esercizio1.cpp posizione.hpp
	g++ -c esercizio1.cpp -o esercizio1.o
esercizio2.o : esercizio2.cpp particella.hpp
	g++ -c esercizio2.cpp -o esercizio2.o
#File oggetto per le librerie
particella.o : particella.hpp particella.cpp
	g++ -c particella.cpp -o particella.o
posizione.o : posizione.hpp posizione.cpp
	g++ -c posizione.cpp -o posizione.o
campovettoriale.o : campovettoriale.cpp campovettoriale.hpp posizione.hpp 
	g++ -c campovettoriale.cpp -o campovettoriale.o
puntomateriale.o : puntomateriale.cpp campovettoriale.hpp posizione.hpp particella.hpp
	g++ -c puntomateriale.cpp -o puntomateriale.o
#Pulizia file oggetti
clean :
	rm *.o
#Pulizia eseguibili
cleanx :
	rm *.x
