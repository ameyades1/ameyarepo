#include <stdio.h>

void hello_world();
void foo();
void bar();

typedef void (*fptr)();
int main(int argc, char* argv[])
{
		foo();
		bar();

		return 0;
}

void hello_world()
{
		printf("Hello World!\n");
}

void foo()
{
/* my_ptr initialized and allocated on stack */
		fptr my_ptr = &hello_world;
}

void bar()
{
/* my_ptr2 uninitialized */

		fptr my_ptr2;
		my_ptr2();
}
