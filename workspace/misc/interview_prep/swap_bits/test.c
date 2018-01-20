
#include <stdio.h>

int main (int argc, char * argv[])
{
	unsigned int a;
	
	if (argc != 2)
		a = 0xAAAA;
	else
		sscanf (argv[1], "%x", &a);
	
	printf ("Swap Odd and Even bits\n");
	printf ("A = %x\n", a);
	
	a = ((a & 0x5555) << 1) | ((a & 0xAAAA) >> 1);
	
	printf ("Bit swapped A = %x\n", a);
	
	return 0;
}
