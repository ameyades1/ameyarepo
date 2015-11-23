#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

node* CreateNode(int data)
{
  node* pNode;

  pNode = (node*)malloc(sizeof(node));

  if(pNode)
  {
    pNode->data  = data;
    pNode->pNext = NULL;
    pNode->pPrev = NULL;
  }

  return pNode;
}


void DeleteNode(node** pNode)
{
  if(pNode != NULL && (*pNode) != NULL)
  {
    free((*pNode));
    (*pNode) = NULL;

  }
}


void DeleteList(node** pHead)
{
  node* pCurr, *pNext;
  pCurr = *pHead;
  pNext = pCurr;

  if(pCurr)
  {
    while(pCurr != NULL)
    {
      pNext = pCurr->pNext;
      DeleteNode(&pCurr);
      pCurr = pNext;
    }

    *pHead = NULL;
  }
}


void PrintList(node* pHead)
{
  node* pTrav = pHead;
  while(pTrav != NULL)
  {
    printf("%d ", pTrav->data);
    pTrav = pTrav->pNext;
  }

  printf("\n");
}


void AddNodeSL(node* pHead, int data)
{
  node* pTrav;

  if(pHead)
  {
    pTrav = pHead;

    while(pTrav->pNext != NULL)
	  pTrav = pTrav->pNext;

    pTrav->pNext = CreateNode(data);
  }
}


void AddNodeDL(node* pHead, int data)
{
  node* pTrav = pHead;
  node* pNew;

  if(pTrav)
  {
    while(pTrav->pNext != NULL)
    {
      pTrav = pTrav->pNext;
    }

    pNew = CreateNode(data);
    pTrav->pNext = pNew;
    pNew->pPrev = pTrav;
  }
}


node* RemoveNodeSL(node* pHead, int data)
{
  node* pCurr, *pPrev;

  pCurr = pHead;
  pPrev = pHead;

  if(pHead == NULL)
    return NULL;

  while(pCurr != NULL)
  {
    if(pCurr->data == data)
      break;

	  pPrev = pCurr;
    pCurr = pCurr->pNext;
  }

  // Node not found

  if(pCurr == NULL)
  {
    return pHead;
  }

  // Node is found

  // Node is head
  if(pCurr == pHead)
  {
    pCurr = pCurr->pNext;
    DeleteNode(&pHead);
    pHead = pCurr;
  }
  else
  {
    pPrev->pNext = pCurr->pNext;
    DeleteNode(&pCurr);
  }

  return pHead;
}

node* RemoveNodeDL(node* pHead, int data)
{
  node* pTrav = pHead;
  node* pTemp;

  if(pHead == NULL)
    return NULL;

  while(pTrav != NULL)
  {
    if(pTrav->data == data)
      break;

    pTrav = pTrav->pNext;
  }

  // Node not found
  if(pTrav == NULL)
    return pHead;

  // Node is found and is head
  if(pTrav == pHead)
  {
    pTemp = pTrav->pNext;
    DeleteNode(&pHead);

    if(pTemp)
      pTemp->pPrev = NULL;

    pHead = pTemp;
  }
  else
  {
    (pTrav->pPrev)->pNext = pTrav->pNext;

    if(pTrav->pNext)
      (pTrav->pNext)->pPrev = pTrav->pPrev;

    DeleteNode(&pTrav);
  }

  return pHead;
}

node* CreateListSL(int aArr[], unsigned int nSize)
{
  node* pHead = NULL;
  unsigned int nIndex;

  for(nIndex = 0; nIndex < nSize; nIndex++)
  {
    if(nIndex == 0)
      pHead = CreateNode(aArr[nIndex]);
    else
      AddNodeSL(pHead, aArr[nIndex]);
  }

  return pHead;
}


node* CreateListDL(int aArr[], unsigned int nSize)
{
  node* pHead = NULL;
  unsigned int nIndex;

  for(nIndex = 0; nIndex < nSize; nIndex++)
  {
    if(nIndex == 0)
      pHead = CreateNode(aArr[nIndex]);
    else
      AddNodeDL(pHead, aArr[nIndex]);
  }

  return pHead;
}


void InsertNodeAfterSL(node* pHead, int nNodeData, int nValInserted)
{
  node* pCurr = pHead;
  node* pNew;

  if(pHead == NULL)
    return;

  while(pCurr != NULL)
  {
    if(pCurr->data == nNodeData)
      break;

    pCurr = pCurr->pNext;
  }

  //  Node not found
  if(pCurr == NULL)
    return;

  pNew = CreateNode(nValInserted);

  pNew->pNext = pCurr->pNext;
  pCurr->pNext = pNew;

}


void InsertNodeAfterDL(node* pHead, int nNodeData, int nValInserted)
{
  node* pTrav;
  node* pNew;

  if(pHead == NULL)
    return;

  pTrav = pHead;
  while(pTrav != NULL)
  {
    if(pTrav->data == nNodeData)
      break;

    pTrav = pTrav->pNext;
  }

  // Data not found
  if(pTrav == NULL)
    return;

  pNew = CreateNode(nValInserted);

  pNew->pPrev = pTrav;
  pNew->pNext = pTrav->pNext;

  if(pTrav->pNext)
    (pTrav->pNext)->pPrev = pNew;

  pTrav->pNext = pNew;

}


node* ReverseListSL(node* pHead)
{
  node *p1, *p2, *p3;

  if(pHead == NULL || pHead->pNext == NULL)
  {
    return pHead;
  }

  p1 = pHead;
  p2 = p1->pNext;

  p1->pNext = NULL;

  do
  {
    p3 = p2->pNext;
    p2->pNext = p1;

    p1 = p2;
    p2 = p3;

  }while(p3 != NULL);

  return p1;

}

node* ReverseListDL(node* pHead)
{
  node* p1, *p2, *pTemp;

  if(pHead == NULL || pHead->pNext == NULL)
    return pHead;

  p1 = pHead;
  p2 = p1->pNext;

  while(p2 != NULL)
  {
    pTemp = p1->pNext;
    p1->pNext = p2->pPrev;
    p2->pPrev = pTemp;

    p1 = p2;
    p2 = p2->pNext;
  }

  return p1;

}


node* ReverseListRecursiveSL(node* p1, node* p2)
{
  node* p3, *pNewHead;

  if(p2)
  {
    p3 = p2->pNext;
  }
  else
  {
    // This is the new head
    return p1;
  }

  if(p2)
    p2->pNext = p1;

  pNewHead = ReverseListRecursiveSL(p2, p3);

  return pNewHead;
}


void DebugDumpNodes(node* pHead)
{
  node* pTrav;
  unsigned int nPrev, nNext;

  if(pHead == NULL)
    return;

  pTrav = pHead;
  while(pTrav != NULL)
  {
    nPrev = (pTrav->pPrev == NULL) ? 0 : pTrav->pPrev->data;
    nNext = (pTrav->pNext == NULL) ? 0 : pTrav->pNext->data;

    printf("Previous: %d   Element: %d   Next: %d\n", nPrev, pTrav->data, nNext);

    pTrav = pTrav->pNext;
  }
}
