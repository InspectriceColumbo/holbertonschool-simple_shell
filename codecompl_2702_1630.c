#ifndef SHELL_H
#define SHELL_H



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>



extern char **environ;/* global environment variable*/

void _puts(char *str);
int _strlen(char *s);
char *_strdup(char *str);
char *concat_all(char *name, char *sep, char *value);
void display_prompt(void);
void sig_handler(int sig_num);
char *read_command(void);
char **split_command(char *line);
int execute_command(char *line);
char **splitstring(char *str, const char *delim);
void execute(char **argv);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

#endif


#include "shell.h"

void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		printf("c$");
		fflush(stdout);
	}
}


#include "shell.h"

char *read_command(void)
{
	size_t bsize = 0; /* getline will dinamically allocate memory */
	char *line = NULL;
	ssize_t len = getline(&line, &bsize, stdin);

	if (len == -1)/* EOF or error */
	{
		if (line == NULL)/* if no input is read */
		{
			return (NULL);
		}
		else
		{
			perror("Error reading input");
			free(line);
			return (NULL);/* return NULL on error */
		}
	}

	return (line);/* return the command if no error */
}

#include "shell.h"
#include <unistd.h>

/**
 * sig_handler - checks if Ctrl C is pressed
 * @sig_num: int
 */

void sig_handler(int sig_num)
{
        if (sig_num == SIGINT)
        {
                write(STDOUT_FILENO, "\nc$ ", 4);  /* Prints prompt after Ctrl+C */
        }
}


#include "shell.h"

int execute_command(char *line)
{
	pid_t pid;
	int status;
	char *args[2];/*array to hold command + NULL for execve */

	/* Preparing the args for execve */
	args[0] = line;
	args[1] = NULL;

	pid = fork();/* child process creation */

	if (pid == -1)
	{
		perror("fork");/* forking has failed */
		return (-1);
	}

	if (pid == 0)/* child process */
	{
		if (execve(line, args, environ) == -1)/*if execve fails print an error*/
		{
			perror("Command execution has failed");
			return (-1);/*failure code instead of exiting*/
		}
	}

	else/* parent process */
	{
		wait(&status);/* wait for child process to finish*/
	}

	return (0);
}

#include "shell.h"

/**
 * main - Entry point of our shell program
 *
 * Return: Always 0 (success).
 */

int main(void)
{
	char *line;
	int status;
	
	signal(SIGINT, sig_handler);/* signal handler for ctrl+c*/

	while (1)/*main shell loop*/
	{
		display_prompt();

		line = read_command();/*read user input*/

		if (line == NULL)
		{
			free(line);
			break;/*EOF/error, exit the shell */
		}

		line[strcspn(line, "\n")] = 0;/*strip newline char if present*/

		if (strlen(line) == 0)/*if empty input(no command typed*/
		{
			free(line);/* ignore empty input */
			continue;/*skip to the next iteration */
		}

		status = execute_command(line);/*execute command*/

		if (status == -1)
		{
			fprintf(stderr, "%s: Command execution failure\n", line);
		}
		free(line);/* free memory allocated for input line*/
	}
	return (0);
}

