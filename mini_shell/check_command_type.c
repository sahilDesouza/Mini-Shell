#include "main.h"


int check_command_type(char * command, char ** external_commands)
{
	int i = 0;
	char * builtIns[] = {"alias", "bg", "bind", "break", "builtin", "case", "cd", "command", "compgen", "complete", "continue", "declare", "dirs", 
	"disown", "echo", "enable", "eval", "exec", "exit", "export", "fc", "fg", "getopts", "hash", "help", "history", "if", "jobs", "kill", "let", "local", "logout", 
	"popd", "printf",  "pushd", "pwd", "read", "readonly", "return", "set", "shift", "shopt", "source", "suspend", "test", "times", "trap",  "type",  "typeset",  
	"ulimit", "umask", "unalias", "unset", "until", "wait", "while", NULL};

	//char * externalCommands[155] = { NULL };

	//To check if its a builtin command or not
	for (i = 0; builtIns[i] != NULL; i++)
	{
		if ((strcmp(command, builtIns[i])) == 0)
		{
			return BUILTIN;
		}
	}
	//to check external command
	//to add commands form .txt file to array of pointers
	//extract_external_commands(externalCommands);
	for (i = 0; external_commands[i] != NULL; i++)
	{
		if ((strcmp(command, external_commands[i])) == 0)
		{
			return EXTERNAL;
		}
	}

	//if no command is passed
	if (strcmp(command, "\n") == 0)
	{
		return NO_COMMAND;
	}
	
		



}