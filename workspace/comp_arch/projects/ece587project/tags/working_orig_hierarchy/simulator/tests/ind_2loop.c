
main()
{
	int i;
	int sum1, sum2;

	sum1 = 0;
	sum2 = 0;

	for (i = 0; i < 10; i++) {
		sum1 += i;
	}

	for (i = 10; i < 20; i++) {
		sum2 += i;
	}

	printf("sum1: %d, sum2: %d, total: %d\n", sum1, sum2, sum1 + sum2);
}
