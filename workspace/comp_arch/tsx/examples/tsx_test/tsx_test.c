#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>

int main(int argc, char* argv[])
{
    printf("TSX Test...\n");
		if (_xbegin() == _XBEGIN_STARTED) {
		  printf ("_xbegin()");
		}
		else {
		  printf("_xabort()"); 
		  _xabort(0xFF);
		}
		
		return 0;
}
