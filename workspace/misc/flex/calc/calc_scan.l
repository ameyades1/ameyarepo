
%%

"+"		{ printf("PLUS \n"); }
"-"		{ printf("MINUS \n"); } 
"/"		{ printf("DIVIDE \n"); }
"*"		{ printf("MULTIPLY \n"); }
"|"		{ printf("ABS \n"); }
[0-9]+  { printf("NUMBER %s\n", yytext); }
[\n]    { printf("NEWLINE \n"); }
[ \t]   { }
.       { printf("Mystery character %s\n", yytext); }

%%

int main(int argc, char* argv[]) 
{
	yylex();
	return 0;
}


