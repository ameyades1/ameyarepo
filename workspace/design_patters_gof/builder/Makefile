all: clean build run

clean:
	rm -rf *.o *.out

build:
	g++ *.cpp -std=c++0x -Wall -g

run:
	./a.out

valgrind: clean build
	valgrind --leak-check=full ./a.out
	

