LIBS:=`root-config --libs`
INCS:=`root-config --cflags`
esercizio10.0 : esercizio10.0.o random.o funzioni.o montecarlo.o
	g++ esercizio10.0.o ${LIBS} ${INCS} random.o funzioni.o montecarlo.o -o esercizio10.0.x
grapherror: grapherror.o random.o funzioni.o montecarlo.o
	g++ grapherror.o ${LIBS} ${INCS} random.o funzioni.o montecarlo.o ../format.cc -o grapherror.x
graphcarlo: graphcarlo.o random.o funzioni.o montecarlo.o
	g++ graphcarlo.o ${LIBS} ${INCS} random.o funzioni.o montecarlo.o ../format.cc -o graphcarlo.x
carlosampling: carlosampling.o random.o funzioni.o montecarlo.o
	g++ carlosampling.o random.o funzioni.o montecarlo.o ../format.cc -o carlosampling.x
provacarlo: provacarlo.o random.o funzioni.o montecarlo.o
	g++ provacarlo.o random.o funzioni.o montecarlo.o ../format.cc -o provacarlo.x
asd: asd.o random.o
	g++ random.o asd.o ${LIBS} ${INCS} -o asd.x
esercizio10.0.o: funzioni.hpp random.hpp montecarlo.hpp esercizio10.0.cpp 
	g++ -c esercizio10.0.cpp ${LIBS} ${INCS} -o esercizio10.0.o 
grapherror.o: funzioni.hpp random.hpp montecarlo.hpp grapherror.cpp ../fmtlib.h
	g++ -c grapherror.cpp ${LIBS} ${INCS} -o grapherror.o 
graphcarlo.o: funzioni.hpp random.hpp montecarlo.hpp graphcarlo.cpp ../fmtlib.h
	g++ -c graphcarlo.cpp ${LIBS} ${INCS} -o graphcarlo.o 
carlosampling.o: funzioni.hpp random.hpp montecarlo.hpp carlosampling.cpp ../fmtlib.h
	g++ -c carlosampling.cpp -o carlosampling.o
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
clean:
	rm *.o