#include "stdlib.h"
#include "stdio.h"
#include "slist.h"


node* create_node(int data)
{
	node* pNode = (node*) malloc( sizeof(node) );
	if(pNode) {
		pNode->data = data;
		pNode->pNext = NULL;
	}
	
	return pNode;
}

void delete_node(node* pNode)
{
	if(pNode) {
		pNode->pNext = NULL;
		free(pNode);
	}
}


// Create a head node
node* slist_create(int data)
{
	node* pHead;
	pHead = create_node(data);
	return pHead;
}


// Add a node 
void slist_add_node(node* pHead, int data)
{
	node* pTemp;
	// List empty
	if(!pHead)
		return;
	
	// Traverse to end of list
	pTemp = pHead;
	while (pTemp->pNext)
		pTemp = pTemp->pNext;
	
	pTemp->pNext = create_node(data);

}


// Print List
void slist_print(node* pHead)
{

	while (pHead)
	{
		printf("%d - ", pHead->data);
		pHead = pHead->pNext;
	}
}


// Insert node after first occurance of data
node* slist_ins_node(node* pHead, int data, int new_data)
{
	node* pCurr, *pPrev, *pNew;

	if (!pHead)
		return NULL;

	// Find first occurance, maintain pointer to previous node
	pCurr = pHead;
	pPrev = pHead;

	while(pCurr && pCurr->data != data)
	{
		pPrev = pCurr;
		pCurr = pCurr->pNext;
	}
	
	// Not found
	if (!pCurr)
		return NULL;
	
	pNew = create_node(new_data);

	// If head
	if (pCurr == pHead)
	{
		pNew->pNext = pHead->pNext;
		pHead->pNext = pNew;
		return pHead;
	}

	// If end
	if (pCurr->pNext == NULL)
	{
		pNew->pNext = NULL;
		pCurr->pNext = pNew;
		return pHead;
	}
	
	// If in between
  pNew->pNext = pCurr->pNext;
	pCurr->pNext = pNew;		
	return pHead;
		
}


// Delete first occurance of data 
node* slist_del_node(node* pHead, int data)
{
	node* pCurr, *pPrev;
	if (!pHead)
		return pHead;
	
	// Find first occurance, maintain pointer to previous node
	pCurr = pHead;
	pPrev = pHead;

	while (pCurr && pCurr->data != data)
	{
		pPrev = pCurr;
		pCurr = pCurr->pNext;
	}
	
	// Not found 
	if (!pCurr)
		return pHead;	
	
	// Found. Three cases-> 
	// pCurr is Head, inbetween or end
	
	// pCurr is Head
	if (pCurr == pHead) 
	{
		pHead = pHead->pNext;
		delete_node(pCurr);
		return pHead;
	}

	// pCurr is end
	if(pCurr->pNext == NULL)
	{
		pPrev->pNext = NULL;
		delete_node(pCurr);
		return pHead;
	}
	
	// pCurr is in between
	pPrev->pNext = pCurr->pNext;
	delete_node(pCurr);	
	return pHead;

}


// Delete list

node* slist_del_list(node* pNode)
{
	node* pTemp;
	if(!pNode)
		return NULL;

	while (pNode)
	{
		pTemp = pNode->pNext;
	  delete_node(pNode);
		pNode = pTemp;
	}
	
	return NULL;
}


// Append List 2 to List 1
node* slist_merge(node* pHead1, node* pHead2)
{
	node* pCurr1 = pHead1;
	if (!pHead1 || !pHead2)
		return NULL;

	// Traverse to end of list 1 
	while (pCurr1->pNext)
		pCurr1 = pCurr1->pNext;

	// Join list1 to list 2
	pCurr1->pNext = pHead2;

	return pHead1;
	
}

// Delete list recursively
void slist_del_list_rec(node* pHead)
{
	if (!pHead)
		return;
	
	slist_del_list_rec(pHead->pNext);
	
	if (pHead)
		delete_node(pHead);		
}

// Print reverse list
void slist_print_rev_rec(node* pHead)
{
	if (!pHead)
		return;
	
	slist_print_rev_rec(pHead->pNext);
	printf("%d - ", pHead->data);
}




