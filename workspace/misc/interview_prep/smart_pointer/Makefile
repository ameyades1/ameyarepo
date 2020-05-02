CC=clang++

all: clean build

build:
	$(CC) -g main.cpp

clean:
	rm -rf *.out

valg: clean build
	valgrind --leak-check=full ./a.out


