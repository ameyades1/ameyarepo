
#include "stdio.h"
#include "slist.h"

int main(int argc, char* argv[])
{

	unsigned int i;
	node* pHead;
	pHead = slist_create(0);
	printf("List Head is... %d\n", pHead->data);
	
	for(i = 0; i < 7; i++)
		slist_add_node(pHead, i);

	slist_print(pHead);
	printf("\n\n");


	slist_del_node(pHead,3); 
	printf("Deleting 3...\n");	
	
	slist_print(pHead);
	printf("\n\n");


	slist_del_node(pHead,0);
	printf("Deleting 0");
	

#if 0
	slist_print(pHead);
	printf("\n\n");


	printf("Inserting 3 after 2\n");
	slist_ins_node(pHead, 2, 3);
		
	slist_print(pHead);
	printf("\n\n");
#endif
	
	pHead = slist_del_list(pHead);
	printf("List Head is... %d\n", pHead ? pHead->data : 0);

	return 0;
}
