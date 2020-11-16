#include "main.h"

int delete_at_last(slist ** head)
{
	int status;
	pid_t wpid;
	if (*head == NULL)
	{
		printf("No processes running\n");
		return LIST_EMPTY;
	}
	
	//condition to check if theres only 1 node present
	if ((*head)->link == NULL)
	{
		
		return slist_delete_first(head);
	}
	
	//create temp pointer to traverse through the nodes
	slist * temp = *head;

	///Traverse till the last node 
	//Below loop checks for NULL in the immediate next node from the current node
	while (temp->link->link != NULL)
	{
		temp = temp->link;
	}
	free(temp->link);
	temp->link = NULL;
	
	return SUCCESS;
}
int slist_delete_first(slist **head)
{
    	//Checking if list empty
    	if (*head == NULL)
	{
		return LIST_EMPTY;
	}

    	//Storing value of head in temp var
    	slist *temp = *head;
    	//Updating head to point to next node
    	*head = (*head)->link;
    	//delete the node
    	free(temp);
    	return SUCCESS;
}