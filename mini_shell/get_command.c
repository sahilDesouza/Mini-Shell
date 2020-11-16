#include "main.h"

char * get_command(char * input_string)
{
	static char command[25] = {'\0'};
	//memset(command, '\0', sizeof(command));
	int i = 0;
	
	//append all the characters into the input string
	while (*input_string != '\0')
	{
		if ((*input_string == ' '))
		{
			break;
		}
		command[i++] = *input_string++;
	}
	

	//adding the null pointer
	command[i] = '\0';

	//return base address
	return command;
	
}