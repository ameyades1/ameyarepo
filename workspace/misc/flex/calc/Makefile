all: clean build

clean:
	rm -rf *.out *.c

build:
	flex calc_scan.l
	gcc lex.yy.c -lfl

