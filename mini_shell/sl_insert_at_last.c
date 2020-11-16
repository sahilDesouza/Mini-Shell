#include "main.h"

int insert_at_last(slist ** head, pid_t data, char * input_string)
{
	
	slist * new = malloc(sizeof(slist));

	if (new == NULL)
	{
		return FAILURE;
	}

	new->data = data;
	new->link = NULL;
	new->count = 1;
	strcpy(new->ext_command_name, input_string);
	//kill(new->data, SIGSTOP);
	

	//if head is null
	if (*head == NULL)
	{
		*head = new;
		printf("[%d]+ \t pid %d has been stopped \t %s\n", new->count, new->data, new->ext_command_name);
		return SUCCESS;
	}
	//if more than 1 node is present
	//take a temp pointer
	slist * temp = *head;
	
	//continuosly add the values at last
	while (temp->link != NULL)
	{
		temp = temp->link;
		new->count++;
		//printf("hi\n");
	}
	temp->link = new;
	new->count++;
	printf("[%d]+ \t pid %d has been stopped \t %s\n", new->count, new->data, new->ext_command_name);
	
	return SUCCESS;
}