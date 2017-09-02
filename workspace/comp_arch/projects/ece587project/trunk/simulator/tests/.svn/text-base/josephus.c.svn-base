
struct node {int key; struct node *next;};

main()
{
	int i, n, m;
	struct node *t, *x;
	m = 7;
	n = 20;
	t = (struct node *) malloc(sizeof *t);
	t->key = 1;
	x = t;
	for (i = 2; i <= n; i++) {
		t->next = (struct node *) malloc(sizeof *t);
		t = t->next;
		t->key = i;
	}
	t->next = x;
	while (t != t->next) {
		for (i = 1; i < m; i++) t = t->next;
		printf("%d ", t->next->key);
		x = t->next;
		t->next = t->next->next;
		free(x);
	}
	printf("%d\n", t->key);
}
	
