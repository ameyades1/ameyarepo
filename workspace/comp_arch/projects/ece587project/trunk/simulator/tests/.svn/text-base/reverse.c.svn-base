
void reverse(char s[], int len);

main()
{
	char s[20];
	int len;

	strcpy(s, "reverse this string");
	len = strlen(s);
	reverse(s, len);
	printf("%s, %d\n", s, len);
}

void reverse(char s[], int len)
{
	int c, i, j;

	for (i = 0, j = len - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}

}
