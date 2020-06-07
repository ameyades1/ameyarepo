CC=clang++
DEFAULT_OPTIONS= -std=c++17 -g

all: clean build

build:
	$(CC) $(DEFAULT_OPTIONS) main.cpp

clean:
	rm -rf *.out

valg: clean build
	valgrind --leak-check=full ./a.out


