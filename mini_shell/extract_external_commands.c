#include "main.h"


void extract_external_commands(char ** external_commands)
{
	//variable declaration
	int fd, i, j;

	char buffer[25] = { '\0' };
	char ch;

	//open .txt file in read mode only

	fd = open("external_commands.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("OPEN");
		exit(1);
	}

	//read the commands and store in the array of pointers
	i = 0, j = 0;

	while (read(fd, &ch, 1) > 0)
	{
		if (ch != '\n')
		{
			buffer[i++] = ch;
		}
		else
		{
			//append null char at the end
			buffer[i] = '\0';
			//allocating memory for external_commands
			external_commands[j] = calloc(strlen(buffer) + 1, sizeof(char));
			strcpy(external_commands[j++], buffer);

			//need to clear the buffer inorder to store the next command in it
			memset(buffer, '\0', 25);

			//reinitialise i to 0 soo that we can read the string from the start
			i = 0;
		}
		
		
	}
	
	
}