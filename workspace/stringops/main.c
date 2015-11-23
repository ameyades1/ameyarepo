#include <stdio.h>
#include "stringops.h"

int main()
{
	char sMyStr[][10] = {"A", "AB", "ABC", "ABCD", "ABCDEF"};
	char sSubstr[] = "BCD";
	char *pMatch = NULL;
  unsigned int i = 0;

#if 0
	for(i = 0; i < 5; i++)
	{
		printf("%s -- ", &sMyStr[i][0]);
		RecursiveReverseString(&sMyStr[i][0], strlen(&sMyStr[i][0]));
		printf("%s \n", &sMyStr[i][0]);
	}
#endif

  for(i = 0; i < 5; i++)
  {
    printf("String %s -- Substring %s -- ", &sMyStr[i][0], sSubstr);
    pMatch = StrStr(&sMyStr[i][0], sSubstr);
    if(pMatch)
      printf("%s found \n", sSubstr);
    else
      printf("not found \n");
  }

  printf("\n");

  printf("Method 1: Number of Ones in %x is %d\n",0, CountAllOnes1(0));
  printf("Method 1: Number of Ones in %x is %d\n",1, CountAllOnes1(1));
  printf("Method 1: Number of Ones in %x is %d\n",0xFF, CountAllOnes1(0xFF));
  printf("Method 1: Number of Ones in %x is %d\n",0x8F, CountAllOnes1(0x8F));

  printf("\n");

  printf("Method 2: Number of Ones in %x is %d\n",0, CountAllOnes2(0));
  printf("Method 2: Number of Ones in %x is %d\n",1, CountAllOnes2(1));
  printf("Method 2: Number of Ones in %x is %d\n",0xFF, CountAllOnes2(0xFF));
  printf("Method 2: Number of Ones in %x is %d\n",0x8F, CountAllOnes2(0x8F));

  printf("\n");

  printf("Toggle all bits of %x is %x\n",0, -1 - 0);
  printf("Toggle all bits of %x is %x\n",1, -1 - 1);
  printf("Toggle all bits of %x is %x\n",0xFF, -1 - 0xFF);
  printf("Toggle all bits of %x is %x\n",0x8F, -1 - 0x8F);

  printf("\n");

  printf("Is %d a Palindrome: %s \n", 0, IsNumPalindrome(0) ? "Yes" : "No");
  printf("Is %d a Palindrome: %s \n", 1, IsNumPalindrome(1) ? "Yes" : "No");
  printf("Is %d a Palindrome: %s \n", 12, IsNumPalindrome(12) ? "Yes" : "No");
  printf("Is %d a Palindrome: %s \n", 101, IsNumPalindrome(101) ? "Yes" : "No");
  printf("Is %d a Palindrome: %s \n", 1221, IsNumPalindrome(1221) ? "Yes" : "No");
  printf("Is %d a Palindrome: %s \n", 12321, IsNumPalindrome(12321) ? "Yes" : "No");
  printf("Is %d a Palindrome: %s \n", 124521, IsNumPalindrome(124521) ? "Yes" : "No");

	return 0;
}
