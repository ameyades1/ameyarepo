/*
 * stringops.h
 *
 *  Created on: Oct 3, 2015
 *      Author: amd
 */

#ifndef STRINGOPS_H_
#define STRINGOPS_H_

/*
 * Type definitions
 */

typedef unsigned char    uint8;
typedef signed char      int8;
typedef unsigned int     uint16;
typedef signed int       int16;
typedef unsigned long    uint32;
typedef signed long      int32;


#define TST_BIT(reg, bit) ((reg) & (1 << (bit)))
#define CLR_BIT(reg, bit) ((reg) &= ~(1 << (bit)))
#define SET_BIT(reg, bit) ((reg) |= 1 << (bit))


/*
 * Function definitions
 */

void ReverseString(char*);
void RecursiveReverseString(char * pStr, int nLen);
char* StrStr(char* pStr, char* pSubStr);

unsigned int CountAllOnes1(unsigned long long int nNum);
unsigned int CountAllOnes2(unsigned long long int nNum);

unsigned char IsNumPalindrome(unsigned int nNum);

#endif /* STRINGOPS_H_ */
