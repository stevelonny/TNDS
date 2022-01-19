compito: compito.o random.o calorimetro.hpp
	g++ compito.o random.o ../format.cc -o compito.x
compito.o : compito.cpp calorimetro.hpp
	g++ -c compito.cpp -o compito.o
random.o: random.cpp
	g++ -c random.cpp -o random.o
clean:
	rm *.o