
void qsort(int v[], int left, int right);
void swap(int v[], int i, int j);

main()
{
	int v[35] = {2, 5, 29, 3, 26, 21, 14, 10, 9, 1, 30, 17, 22, 25, 4,
		     27, 8, 19, 6, 16, 18, 7, 11, 12, 20, 23, 15, 13, 28, 24,
		     5, 10, 15, 20, 25};

	int i;

	qsort(v, 0, 34);

	printf("\n");
	for (i = 0 ; i < 35; i++)
		printf("%d ", v[i]);
	printf("\n");
}

void qsort(int v[], int left, int right)
{
	int i, last;

	if (left >= right) return;
	swap(v, left, (left + right)/2);
	last = left;

	for (i = left + 1; i <= right; i++)
		if (v[i] < v[left]) swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

void swap(int v[], int i, int j)
{
	int temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
