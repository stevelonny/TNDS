LIBS:=`root-config --libs`
INCS:=`root-config --cflags`
compito: compito.o random.o resistenza.hpp
	g++ compito.o random.o ${LIBS} ${INCS} -o compito.x
compito.o : compito.cpp resistenza.hpp
	g++ -c compito.cpp ${LIBS} ${INCS} -o compito.o
random.o: random.cpp
	g++ -c random.cpp -o random.o
clean:
	rm *.o