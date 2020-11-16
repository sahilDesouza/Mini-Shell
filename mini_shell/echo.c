#include "main.h"

void echo(char * input_string, int status)
{

	if (!strcmp(input_string, "echo $?"))
	{
		//to print exit status
		printf("%d\n", WEXITSTATUS(status));
	}
	else if (!strcmp(input_string, "echo $$"))
	{
		//to print pid of SHELL
		printf("%d\n", getpid());
	}
	else if (!strcmp(input_string, "echo $SHELL"))
	{
		//to print shell current path
		system("pwd");
	}
	
}