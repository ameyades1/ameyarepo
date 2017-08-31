#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#define TRUE  (1)
#define FALSE (0)


typedef unsigned char bool;

typedef struct node
{
	unsigned int data;
	struct node* pNext;
	struct node* pPrev;
}node;

node* CreateNode(int data);

void DeleteNode(node** pNode);

void DeleteList(node** pHead);

void PrintList(node* pHead);

node* CreateListSL(int aArr[], unsigned int nSize);

node* CreateListDL(int aArr[], unsigned int nSize);

void AddNodeSL(node* pHead, int data);

void AddNodeDL(node* pHead, int data);

node* RemoveNodeSL(node* pHead, int data);

node* RemoveNodeDL(node* pHead, int data);

void InsertNodeAfterSL(node* pHead, int nNodeData, int nValInserted);

void InsertNodeAfterDL(node* pHead, int nNodeData, int nValInserted);

node* ReverseListSL(node* pHead);

node* ReverseListDL(node* phead);

node* ReverseListRecursiveSL(node* p1, node* p2);

void DebugDumpNodes(node* pHead);

#endif
