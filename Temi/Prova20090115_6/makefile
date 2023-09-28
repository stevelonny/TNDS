LIBS:=`root-config --libs`
INCS:=`root-config --cflags`
compito : compito.cpp random.o compito.o
	g++ random.o ../format.cc ${LIBS} ${INCS} compito.o -o compito.x
compito.o : esperimento.hpp random.hpp compito.cpp
	g++ -c compito.cpp ${LIBS} ${INCS} -o compito.o
random.o : random.cpp random.hpp
	g++ -c random.cpp -o random.o
clean:
	rm *.o