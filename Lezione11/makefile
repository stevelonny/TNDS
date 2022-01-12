LIBS:=`root-config --libs`
INCS:=`root-config --cflags`
main : main.cpp esperimento.o random.o main.o
	g++ random.o esperimento.o ${LIBS} ${INCS} main.o -o main.x
main.o : esperimento.hpp random.hpp main.cpp
	g++ -c main.cpp ${LIBS} ${INCS} -o main.o
esperimento.o : esperimento.cpp esperimento.hpp random.hpp
	g++ -c esperimento.cpp ${LIBS} ${INCS} -o esperimento.o
random.o : random.cpp random.hpp
	g++ -c random.cpp -o random.o
clean:
	rm *.o