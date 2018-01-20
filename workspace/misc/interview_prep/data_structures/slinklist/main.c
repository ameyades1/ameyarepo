#include "stdio.h"
#include "slist.h"

int main(int argc, char* argv[])
{

	unsigned int i;
	node* pHead, *pHead2;
	pHead = slist_create(0);
	printf("List Head is... %d\n", pHead->data);
	
	for(i = 0; i < 7; i++)
		slist_add_node(pHead, i);

	slist_print(pHead);
	printf("\n\n");

	printf("Deleting 3...\n");	
	slist_del_node(pHead,3); 
	
	slist_print(pHead);
	printf("\n\n");

	pHead = slist_del_node(pHead,0);
	printf("Deleting 0...\n\n");
	
	slist_print(pHead);
	printf("\n\n");

	printf("Inserting 3 after 2\n");
	slist_ins_node(pHead, 2, 3);
		
	slist_print(pHead);
	printf("\n\n");

//--------------------------------------------
	printf("Create List 2...\n");
	pHead2 = slist_create(20);
	for(i = 21; i < 25; i++)
		slist_add_node(pHead2, i);

	pHead = slist_merge(pHead, pHead2);

	printf("The merged list is...\n");
	slist_print(pHead);
	printf("\n\n");

	printf ("Printing reverse list... \n");
	slist_print_rev_rec(pHead);
	printf("\n\n");

//---------------------------------------------	
	slist_del_list_rec(pHead);
//	pHead = NULL;
	printf("Deleting list recusively... \nList Head is... %d\n", pHead ? pHead->data : 0);
	
//	pHead = slist_create (10);
	printf("Sizeof pHead = %d, Sizeof int = %d, Sizeof node = %d\n", sizeof(pHead), sizeof(int), sizeof(node));
	return 0;
}
