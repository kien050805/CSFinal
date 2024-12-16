all: mytests

mytests: mytests.o 
	g++ -std=c++11 -o mytests mytests.o 
	./mytests

mytests.o: mytests.cpp MinPriorityQueue.cpp MinPriorityQueue.hpp Graph.cpp Graph.hpp
	g++ -std=c++11 -o mytests.o -c mytests.cpp 

clean:
	rm -f *.o mytests
	clear