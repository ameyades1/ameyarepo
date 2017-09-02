
void rule(int l, int r, int h);

main()
{
	rule(0, 16, 4);
}

void rule(int l, int r, int h)
{
	int m = (l + r)/2;
	if (h > 0) {
		printf("position %d, height %d\n", m, h);
		rule(l, m, h - 1);
		rule(m, r, h - 1);
	}
}
