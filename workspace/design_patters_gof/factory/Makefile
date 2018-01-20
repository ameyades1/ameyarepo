all: clean build run

clean:
	rm -rf *.o *.out Doxyfile* html latex

build:
	g++ *.cpp -std=c++0x -Wall -g

run:
	./a.out

valgrind: clean build
	valgrind --leak-check=full ./a.out
	
doc:  
	doxygen -g
	doxygen Doxyfile
	cd latex && $(MAKE) all
	acroread latex/refman.pdf&


