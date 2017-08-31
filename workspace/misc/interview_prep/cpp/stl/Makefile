all: clean build

clean:
	rm -rf *.o *.log main

COPTS= -Wall -std=c++11
CDBGOPTS = -Wall -std=c++11 -g
build:
	g++ -c complex.cpp -o complex.o $(COPTS)
	g++ -c main.cpp -o main.o -Wall $(COPTS)
	g++ -o main main.o complex.o -Wall $(COPTS)

dbg:
	g++ -c complex.cpp -o complex.o $(CDBGOPTS)
	g++ -c main.cpp -o main.o -Wall $(CDBGOPTS)
	g++ -o main main.o complex.o -Wall $(CDBGOPTS)
