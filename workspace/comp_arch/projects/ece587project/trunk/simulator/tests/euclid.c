main()
{
	int u, v, t, x, y;

	u = x = 1248480;
	v = y = 4187610; 

	while (u > 0) {
		if (u < v) {
			t = u;
			u = v;
			v = t;
		}
		u = u - v;
	}

	printf("gcd(%d, %d) = %d\n", x, y, v);
}
