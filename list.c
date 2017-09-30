#include "stdio.h"
#include "string.h"
#include "stdlib.h"
int main()
{
	char command[50];
	strcpy(command, "ls -lah");

	system(command);
// TO DO, REPLACE SYSTEM() WITH FORK() AND THEN EXECV()

	return 0;
}

