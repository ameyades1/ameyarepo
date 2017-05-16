#ifndef __SLIST_H__
#define __SLIST_H__


typedef struct _node {
	int data;
	struct _node* pNext;
}node;


// Generic create / delete functions
node* create_node(int data);

void delete_node(node* pNode);

// Create a head node
node* slist_create(int data);

// Append a node
void slist_add_node(node* pHead, int data);

// Insert node after first occurance of data
node* slist_ins_node(node* pNode, int data, int new_data);

// Delete first occurance of data 
node* slist_del_node(node* pNode, int data);

// Delete list
node* slist_del_list(node* pNode);

// Print List
void slist_print(node* pHead);

#endif


