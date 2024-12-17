all: mytests

mytests: mytests.o 
	g++ -std=c++11 -o mytests mytests.o 
	./mytests

mytests.o: mytests.cpp MinPriorityQueue.cpp MinPriorityQueue.hpp Graph.cpp Graph.hpp
	g++ -std=c++11 -o mytests.o -c mytests.cpp 

CLI: CLI.o 
	g++ -std=c++11 -o CLI CLI.o 
	./CLI

CLI.o: CLI.cpp MinPriorityQueue.cpp MinPriorityQueue.hpp Graph.cpp Graph.hpp
	g++ -std=c++11 -o CLI.o -c CLI.cpp

clean:
	rm -f *.o mytests
	clear