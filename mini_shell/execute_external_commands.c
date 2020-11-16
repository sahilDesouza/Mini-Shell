#include "main.h"

extern slist *head;
extern int status;

void execute_external_commands(char *input_string)
{
	//store process id
	pid_t pid; 

    	//Variable declaration
    	int i = 0, j = 0;
    	int number_of_words = 0;
	//To save indices of each command seprated by pipe
    	int index_of_cmd[20]; 
    	int number_of_pipes = 0;
    	
    	//An array of pointers to null-terminated strings that represent the input argument list needed for exec function
    	char *words[10] = {NULL};
	char stringCopy[20];
	strcpy(stringCopy, input_string);

    	//Extracting words from input_string
    	char *path = strtok(input_string, " ");
    	while (path != NULL)
    	{
        	words[i++] = path;
        	path = strtok(NULL, " ");
    	}
    	number_of_words = i;
	
    	//Save respective indices of commands present in the argument list(words) whatever comes after pipe character is treated as a command
    	index_of_cmd[0] = 0;
    	j = 0;
    	for (i = 0; i < number_of_words; i++)
    	{
        	if (strcmp(words[i], "|") == 0)
        	{
			//Replace pipe character in argument list with NULL
            		words[i] = NULL; 
            		index_of_cmd[++j] = i + 1;
		}
    	}

   	number_of_pipes = j;
	//Create an array to store pipe fds
    	int pipe_fds[number_of_pipes][2]; 

    	//Create n pipes
    	for (i = 0; i < number_of_pipes; i++)
    	{
        	if (pipe(pipe_fds[i]) == -1)
        	{
            		//Error handling
            		perror("pipe");
            		exit(EXIT_FAILURE);
        	}
    	}

    	//Create number_of_pipes + 1 number of child processes
    	for (i = 0; i <= number_of_pipes; i++)
    	{
       		pid = fork();

        	if (pid == -1)
        	{
            		//Error handling
            		perror("fork");
            		exit(EXIT_FAILURE);
        	}
        	else if (pid == 0) //Child
        	{
			//For the first command
            		if (i == 0) 
            		{
				//Redirect stdout stream to write end of current pipe
                		dup2(pipe_fds[0][1], STDOUT_FILENO); 
            		}
			//For the last command
            		else if (i == number_of_pipes) 
            		{
				//Redirect input stream to write end of previous pipe
                		dup2(pipe_fds[i - 1][0], STDIN_FILENO); 
            		}
			//For the commands in between
            		else 
            		{
				//Redirect stdin stream to read from read end of previous pipe
                		dup2(pipe_fds[i - 1][0], STDIN_FILENO);
				//Redirect stdout stream to write end of current pipe
                		dup2(pipe_fds[i][1], STDOUT_FILENO);    
            		}

            		//close all ends of pipes before calling exec function
            		for (int k = 0; k < number_of_pipes; k++)
            		{
                		for (int t = 0; t < 2; t++)
                		{
                    			close(pipe_fds[k][t]);
                		}
            		}

            		//execute command
            		execvp(words[index_of_cmd[i]], &words[index_of_cmd[i]]);
            		exit(EXIT_FAILURE);
        	}
   	}

    	//close all ends of pipes in parent
    	for (int k = 0; k < number_of_pipes; k++)
    	{
		for (int t = 0; t < 2; t++)
        	{
            		close(pipe_fds[k][t]);
       		}
    	}
    

    	//wait for termination of children
    	for (i = 0; i <= number_of_pipes; i++)
    	{
        	//wait for state changes in child
        	waitpid(-1, &status, 0 | WUNTRACED);
   	}

    	//Obtain information about the process whose state has changed 
	//check if the child terminated normally
    	if (WIFEXITED(status)) 
    	{
       		printf("\nChild with PID: %d terminated normally\n", pid);
    	}
	//check if the child process was terminated by a signal
    	else if (WIFSIGNALED(status)) 
    	{
        	printf("\nchild with PID %d terminated by signalling", pid);

        	//Get signal number of signal that caused the child process to terminate
        	printf("\nSignal number: %d\n", WTERMSIG(status));
    	}
    	else if (WIFSTOPPED(status)) //check if child was stopped (paused) by delivery of a signal
    	{
		printf("\n");
		//Save child pid in linked list
        	insert_at_last(&head, pid, stringCopy); 
        	//printf("pid %d has been stopped\n", pid);
		printf("Signal number = %d\n", WSTOPSIG(status));
    	}
}
