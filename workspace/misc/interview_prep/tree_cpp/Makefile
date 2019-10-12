CC=clang++
CC_OPTS=--std=c++11 -g
SRC_PATH=src

all: clean build

clean:
	rm -rf *.o main

build:
	$(CC) $(CC_OPTS) $(SRC_PATH)/main.cpp -o main

