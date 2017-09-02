
main()
{
	int v[35] = {2, 5, 29, 3, 26, 21, 14, 10, 9, 1, 30, 17, 22, 25, 4,
		     27, 8, 19, 6, 16, 18, 7, 11, 12, 20, 23, 15, 13, 28, 24,
		     5, 10, 15, 20, 25};

	int n = 35;
	int gap, i, j, temp;

	for (gap = n/2; gap > 0; gap /= 2)
		for (i = gap; i < n; i++)
			for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap)
			{
				temp = v[j];
				v[j] = v[j + gap];
				v[j + gap] = temp;
			}

	printf("\n");
	for (i = 0 ; i < n; i++)
		printf("%d ", v[i]);
	printf("\n");
}
