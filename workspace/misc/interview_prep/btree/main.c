#include <stdio.h>
#include "btree.h"

int aArr[] = {119, 35, 4, 9, 678, 12, 2};
unsigned int nSize = sizeof(aArr) / sizeof(aArr[0]);

int main()
{
  node* pRoot;

  pRoot = CreateBtree(aArr,nSize);

  printf("\nInorder Traversal \n");
  TravBtreeInorder(pRoot);
  printf("\n");

  printf("\nPostorder Traversal \n");
  TravBtreePostorder(pRoot);
  printf("\n");

  printf("\nPreorder Traversal \n");
  TravBtreePreorder(pRoot);
  printf("\n");

  return 0;
}
