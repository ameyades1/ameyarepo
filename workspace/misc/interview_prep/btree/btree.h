#ifndef __BTREE_H__
#define __BTREE_H__

#define TRUE  (1)
#define FALSE (0)


typedef unsigned char bool;

typedef struct node
{
	unsigned int data;
	struct node* pRight;
	struct node* pLeft;
}node;

node* CreateNode(int data);

void DeleteNode(node** pNode);

void AddNode(node* pRoot, int data);

node* CreateBtree(int aArr[], unsigned int nSize);

void TravBtreeInorder(node* pRoot);

void TravBtreePostorder(node* pRoot);

void TravBtreePreorder(node* pRoot);

#endif
