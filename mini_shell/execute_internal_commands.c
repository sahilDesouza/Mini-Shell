#include "main.h"

slist * head = NULL;
//extern pid_t pid;
extern int status;
void execute_internal_commands(char * input_string)
{
	char *path;
	char pwd_path[PATH_MAX];
	//char * pwd_path;

	//if internal command is exit, then need to terminate the shell immediately
	if (!strcmp("exit", input_string))
	{
		exit(1);
	}
	//if internal command is pwd, then required to display current working directory
	else if (!strcmp("pwd", input_string))
	{
		getcwd(pwd_path, sizeof(pwd_path));
		//pwd_path = getwd(NULL);
		printf("%s\n", pwd_path);
	}
	else if (!strncmp("cd", input_string, 2))
	{
		path = strtok(input_string, " ");
		path = strtok(NULL, " ");

		//to change the path to the specified path
		if (chdir(path) == -1)
		{
			perror("chdir");
		}
	}
	else if (strcmp("fg", input_string) == 0)
	{
		//need to resume the last process and delete it from linked list
		//delete_at_last(&head);
		pid_t pid = slist_get_last(head);
		if (pid)
		{
			printf("Process with pid: %d has resumed\n", pid);

            		kill(pid, SIGCONT);
            		waitpid(pid, &status, 0 | WUNTRACED);

            		//Obtain information about the process whose state has changed 
			//check process terminated normally
           		if (WIFEXITED(status)) 
            		{
                		printf("\nChild with PID: %d terminated normally\n", pid);
            		}
			//check if process was terminated by a signal
            		else if (WIFSIGNALED(status)) 
            		{
                		printf("\nchild with PID %d terminated by signaling", pid);
                		//Get signal number of signal that caused the child process to terminate
                		printf("\nSignal number: %d\n", WTERMSIG(status));
            		}
			//check if process was stopped (paused) by delivery of a signal
            		else if (WIFSTOPPED(status)) 
            		{
				//Save pid in linked list
                		insert_at_last(&head, pid, input_string); 
               			printf("\nchild with PID %d terminated by signaling", pid);
                		//Get signal number of signal that caused the child process to stop
                		printf("\nSignal number: %d\n", WSTOPSIG(status));
            		}
			//delete the process name from the linked list
            		delete_at_last(&head);
		}
		
		
	}
	else if (!strcmp("jobs", input_string))
	{
		//need to resume the last process and delete it from linked list
		print_slist(head);
		
	}
	/*Resume a suspended job in the background*/
    	else if (strcmp("bg", input_string) == 0)
    	{
        	pid_t pid = slist_get_last(head);
        
        	if (pid)
        	{
			//continue process in the background
            		kill(pid, SIGCONT);
			//delete the process name from the linked list
            		delete_at_last(&head);
        	}
    	}
	
}