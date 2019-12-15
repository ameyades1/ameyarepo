CC=clang++
CC_OPTS=--std=c++11 -g -O4
SRC_PATH=src

all: clean build

clean:
	rm -rf *.o main

build:
	$(CC) $(CC_OPTS) $(SRC_PATH)/main.cpp -o main

