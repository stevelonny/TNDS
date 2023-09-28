LIBS:=`root-config --libs`
INCS:=`root-config --cflags`
compito: compito.o random.o
	g++ compito.o random.o ../format.cc ${LIBS} ${INCS} -o compito.x
compito.o: random.hpp resistenza.hpp compito.cpp ../fmtlib.h
	g++ -c compito.cpp ${LIBS} ${INCS} -o compito.o
random.o: random.cpp random.hpp
	g++ -c random.cpp -o random.o
clean:
	rm *.o