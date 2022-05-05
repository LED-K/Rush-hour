


All:final

final: main.o terrain.o vehicule.o solver.o
	g++  -g -std=c++0x -o  final terrain.o solver.o vehicule.o main.o -W -Wall  -pedantic

main.o: main.cpp  solver.o
	g++ -g -std=c++0x -o main.o  -c main.cpp -W -Wall  -pedantic

solver.o: solver.cpp  solver.h 
	g++ -g -std=c++0x  -o solver.o -c solver.cpp -W -Wall  -pedantic


terrain.o: terrain.cpp terrain.h
	g++ -g -std=c++0x -o terrain.o -c terrain.cpp -W -Wall  -pedantic

vehicule.o: vehicule.cpp terrain.h
	g++ -g -std=c++0x -o vehicule.o -c vehicule.cpp -W -Wall  -pedantic



clean:
	rm *.o
				