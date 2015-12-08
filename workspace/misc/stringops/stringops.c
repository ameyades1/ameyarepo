/*
 * stringops.c
 *
 *  Created on: Oct 3, 2015
 *      Author: amd
 */

#include <stdio.h>
#include <string.h>
#include "stringops.h"

void ReverseString(char* str)
{
  unsigned int nLen;
  unsigned int nIndex;
  char cTemp;

  // Argument check
  if(str == NULL)
    return;

  nLen = strlen(str);

  for(nIndex = 0; nIndex < nLen/2; nIndex++)
  {
    cTemp = str[nIndex];
    str[nIndex] = str[nLen - 1 - nIndex];
    str[nLen - 1 - nIndex] = cTemp;
  }
}


void RecursiveReverseString(char * pStr, int nLen)
{
  char cTemp;

  if(nLen > 0)
  {
  	cTemp = *pStr;
	  *pStr = *(pStr + nLen - 1);
	  *(pStr + nLen - 1) = cTemp;

	  RecursiveReverseString(pStr + 1, nLen - 2);
  }
}


char* StrStr(char* pStr, char* pSubStr)
{
  char* pCurrStr, *pMatch, *pCurrSubStr;

  if(pStr == NULL || pSubStr == NULL)
    return NULL;

  pCurrStr = pStr;
  pCurrSubStr = pSubStr;

  // Find the first matching character
  while((*pCurrStr != *pCurrSubStr) && *pCurrStr != '\0')
    pCurrStr++;

  // If we reach the end, not found
  if(*pCurrStr == '\0')
    return NULL;

  // Else store the matching position
  pMatch = pCurrStr;

  // Continue till we match all substring chars
  while((*pCurrStr == *pCurrSubStr) && (*pCurrStr != '\0') && (pCurrSubStr != '\0'))
  {
    pCurrStr++;
    pCurrSubStr++;
  }

  // If we reach the end, the whole substring matched
  if (*pCurrSubStr == '\0')
    return pMatch;
  else
    return NULL;

}


unsigned int CountAllOnes1(unsigned long long int nNum)
{
  unsigned int nBits = 0;

  while(nNum !=0)
  {
    nBits += nNum & 1;
    nNum >>= 1;
  }

  return nBits;

}


static unsigned int BitMap16[] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};
unsigned int CountAllOnes2(unsigned long long int nNum)
{
  unsigned int nBits;

  nBits = BitMap16[(nNum >> 0)  & 0x0F] +
          BitMap16[(nNum >> 4)  & 0x0F] +
          BitMap16[(nNum >> 8)  & 0x0F] +
          BitMap16[(nNum >> 12) & 0x0F];

  return nBits;
}


unsigned char IsNumPalindrome(unsigned int nNum)
{
  unsigned nOriginal = nNum;
  unsigned int nRevNum = 0;
  unsigned int nDigit = 0;

  // Reverse the number
  while(nNum != 0)
  {
    nDigit = nNum % 10;
    nRevNum = (nRevNum * 10 + nDigit);

    nNum /= 10;
  }

  if (nOriginal == nRevNum)
    return 1;
  else
    return 0;

}
