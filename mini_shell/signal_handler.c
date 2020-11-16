#include "main.h"

extern pid_t pid;
void signal_handler(int sig_num)
{
	if (pid > 0)
	{
		if (sig_num == SIGINT)
		{
			//terminating the process
			kill(pid, SIGKILL);
		}
		else if (sig_num == SIGTSTP)
		{
			//stopping the process 
			kill(pid, SIGSTOP);
			//printf("pid %d has been stopped\n", head->data);
			
			
		}
		
		
	}
	

}