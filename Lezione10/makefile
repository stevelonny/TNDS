LIBS:=`root-config --libs`
INCS:=`root-config --cflags`
provacarlo: provacarlo.o random.o funzioni.o montecarlo.o
	g++ provacarlo.o random.o funzioni.o montecarlo.o ../format.cc -o provacarlo.x
asd: asd.o random.o
	g++ random.o asd.o ${LIBS} ${INCS} -o asd.x
provacarlo.o: funzioni.hpp random.hpp montecarlo.hpp provacarlo.cpp ../fmtlib.h
	g++ -c provacarlo.cpp -o provacarlo.o
asd.o : random.hpp asd.cpp 
	g++ -c asd.cpp ${LIBS} ${INCS} -o asd.o
random.o : random.cpp random.hpp
	g++ -c random.cpp -o random.o
funzioni.o : funzioni.hpp funzioni.cpp
	g++ -c funzioni.cpp -o funzioni.o
montecarlo.o: funzioni.hpp random.hpp montecarlo.hpp montecarlo.cpp
	g++ -c montecarlo.cpp -o montecarlo.o
clean: *.o
	rm *.o