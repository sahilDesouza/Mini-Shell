#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h> 
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <limits.h>

#define BUILTIN 1
#define EXTERNAL 2
#define NO_COMMAND 3

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

typedef pid_t data_t;

typedef struct node
{
	data_t data;
	struct node * link;
	char ext_command_name[50];
	int count;

}slist;
enum status
{
	FAILURE,
	SUCCESS,
	LIST_EMPTY,
	DATA_NOT_FOUND,
	DATA_PRESENT
};

//prototype for linked list
int insert_at_last(slist **, pid_t, char *);
void print_slist(slist *);
int delete_at_last(slist **);
int slist_delete_first(slist **head);
pid_t slist_get_last(slist *head);

//prototypes for mini shell
void scan_input(char * prompt, char * input_string);
char * get_command(char * input_string);
int check_command_type(char * command, char ** external_commands);
void echo(char * input_string, int status);
void execute_internal_commands(char * input_string);
void signal_handler(int sig_num);
void extract_external_commands(char ** external_commands);
void execute_external_commands(char *input_string);

#endif