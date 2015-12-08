#include <stdio.h>
#include <stdlib.h>

#include "btree.h"

node* CreateNode(int data)
{
  node* pNode;

  pNode = (node*)malloc(sizeof(node));

  if(pNode)
  {
    pNode->data  = data;
    pNode->pRight = NULL;
    pNode->pLeft = NULL;
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

void AddNode(node* pRoot, int data)
{
  node* pNode;
  node* pTrav, *pTemp;

  if(pRoot == NULL)
    return;

  pNode = CreateNode(data);
  pTrav = pRoot;

  while(pTrav)
  {
    pTemp = pTrav;
    if(pTrav->data <= data)
      pTrav = pTrav->pLeft;
    else
      pTrav = pTrav->pRight;
  }

  if(pTemp->data <= data)
    pTemp->pLeft = pNode;
  else
    pTemp->pRight = pNode;

}


node* CreateBtree(int aArr[], unsigned int nSize)
{
  node* pRoot;
  unsigned int nIndex;

  if(nSize == 0)
    return NULL;

  for(nIndex = 0; nIndex < nSize; nIndex++)
  {
    if(nIndex == 0)
      pRoot = CreateNode(aArr[nIndex]);
    else
      AddNode(pRoot,aArr[nIndex]);
  }

  return pRoot;
}


void TravBtreeInorder(node* pRoot)
{

  if(pRoot == NULL)
    return;

  TravBtreeInorder(pRoot->pRight);
  printf("%d-", pRoot->data);
  TravBtreeInorder(pRoot->pLeft);

}


void TravBtreePostorder(node* pRoot)
{

  if(pRoot == NULL)
    return;

  TravBtreePostorder(pRoot->pRight);
  TravBtreePostorder(pRoot->pLeft);
  printf("%d-", pRoot->data);

}


void TravBtreePreorder(node* pRoot)
{

  if(pRoot == NULL)
    return;

  TravBtreePreorder(pRoot->pLeft);
  TravBtreePreorder(pRoot->pRight);
  printf("%d-", pRoot->data);

}
