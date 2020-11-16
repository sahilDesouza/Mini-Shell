/*
*	AUTHOR: SAHIL DESOUZA
*   	PROJECT: MINI SHELL
* 	DATE: 29/10/2020
*/

#include "main.h"

pid_t pid;
extern slist * head;
int status;
void scan_input(char * prompt, char * input_string)
{
	char * command;
	
	int command_type, ret_status, status;
	char *external_commands[155] = {NULL};
	//to add commands form .txt file to array of pointers to my array of pointers
	extract_external_commands(external_commands);

	//register signal for sigint and sigtstp
	signal(SIGINT, signal_handler);
	signal(SIGTSTP, signal_handler);

	while (1)
	{
		
		//to display prompt
		printf(ANSI_COLOR_GREEN"[%s]$ "ANSI_COLOR_RESET, prompt);

		//flush the output buffer
		fflush(stdout);

		//to read input from user
		scanf("%[^\n]", input_string);
		getchar();

		//to change prompt name to a name user-defined
		if ((strncmp("PS1=", input_string, 4)) == 0)
		{
			if (input_string[4] != ' ')
			{
				strcpy(prompt, &input_string[4]);
			}
			else
			{
				printf("ERROR:command not found\n");
			}
			
			memset(input_string, '\0', 25);
			continue;
		}
	
		//to get internal/external command
		command = get_command(input_string);
		//printf("command is : %s\n", command);

		//to check command type
		command_type = check_command_type(command, external_commands);

		if (command_type == EXTERNAL)
		{
			execute_external_commands(input_string);
		}
		else if (command_type == BUILTIN)
		{
			//internal command executed 
			execute_internal_commands(input_string);

			//call echo function to print $?, $$, $SHELL
			echo(input_string, status);
		}
		
		else if ((command_type != BUILTIN) && (command_type != EXTERNAL) && (command_type != NO_COMMAND) && (strncmp("PS1=", input_string, 4) != 0))
		{
			//print error
			printf("ERROR:command not found\n");
		}
		//reset input string to null
		memset(input_string, '\0', 25);
		
	}
	
}