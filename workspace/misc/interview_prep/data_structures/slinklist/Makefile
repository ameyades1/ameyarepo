
CC=gcc
CCFLAGS=-I.
DEPS=slist.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS) -g
clean: 
	rm -rf main main.o slist.o

all:main.o slist.o
	$(CC) -o main main.o slist.o -I. -g

