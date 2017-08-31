#include <stdio.h>
#include "linkedlist.h"

int aArr[] = {119, 35, 4, 9, 678, 12, 2};
unsigned int nSize = sizeof(aArr) / sizeof(aArr[0]);

int main()
{
  node* pHead, *pNewHead;

  pHead = CreateListDL(aArr, nSize);
  PrintList(pHead);

  AddNodeDL(pHead, 110);
  printf("\nAdding 110\n");
  PrintList(pHead);

  InsertNodeAfterDL(pHead, 4, 5);
  printf("\nInsert 5 after 4\n");
  PrintList(pHead);

  InsertNodeAfterDL(pHead, 678, 15);
  printf("\nInsert 15 after 678\n");
  PrintList(pHead);

  InsertNodeAfterDL(pHead, 110, 215);
  printf("\nInsert 215 after 110\n");
  PrintList(pHead);

  pHead = RemoveNodeDL(pHead, 5);
  printf("\nRemove 5 \n");
  PrintList(pHead);

#if 1
  pHead = ReverseListDL(pHead);
  printf("\nReverse List \n");
  PrintList(pHead);

#endif
#if 0
  pHead = ReverseListSL(pHead);
  printf("\nReverse List \n");
  PrintList(pHead);

  pNewHead = ReverseListRecursiveSL(pHead, pHead->pNext);
  pHead->pNext = NULL;
  pHead = pNewHead;
  printf("\nReverse List \n");
  PrintList(pHead);
#endif


  DeleteList(&pHead);
  printf("\nDelete list \n");
  PrintList(pHead);

  return 0;
}
