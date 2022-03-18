/*********************************************************************************************/
/* This code enables the user to display the environment variables                           */
/*********************************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//display environment variables
int main(int argc, char **argv, char ** envp)
{
	int i;

	printf("\n");
	printf("********************   The environment variables:    ******************** \n");
	printf("\n");
	while(*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}

	printf("LOL = %s\n", getenv("LOL"));
	
	return 0;
}
