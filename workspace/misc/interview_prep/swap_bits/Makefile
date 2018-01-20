clean: 
	rm -rf test test.o

all: clean
	gcc -c test.c 
	gcc -o test test.o

debug:
	gcc -c test.c -g
	gcc -o test test.o -g

run:
	./test

