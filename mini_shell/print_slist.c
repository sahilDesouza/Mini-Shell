#include "main.h"

void print_slist(slist * head)
{
	
	if (head == NULL)
   	{
		printf("No jobs running\n");
   	}
     	else
    	{
		printf("jobs running are\n");
        	while(head)
        	{
			printf("[%d] \t stopped \t pid %d \t command: %s\n", head->count, head->data ,head->ext_command_name);
			head = head->link;
			
		}
    	}
}

pid_t slist_get_last(slist *head)
{
	//Checking if list empty
	if (head == NULL)
	{
		printf("\nList is empty\n");
		return 0;
	}
	else
	{
		while (head->link != NULL)
		{
			head = head->link;
		}
		return head->data;
	}
}