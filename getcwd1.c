#include "stdio.h"
#include "string.h"
#include "stdlib.h"
int main()
{
	char s[256];
	getcwd(s, 50);

	printf("%s\n", s);
	return 0;
}

