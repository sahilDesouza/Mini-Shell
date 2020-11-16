/*
*	AUTHOR: SAHIL DESOUZA
*   PROJECT: MINI SHELL
* 	DATE: 29/10/2020
*/

#include "main.h"

int main(int argc, char ** argv)
{
	//clear the output screen
	system("clear");

	//to store prompt name
	char prompt[25] = "MiniShell";

	//to read command
	char input_string[25];

	//function to perform appropriate action on the cmd provided
	scan_input(prompt, input_string);

	return 0;
}
    