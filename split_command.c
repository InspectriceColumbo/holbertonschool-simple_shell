#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * split_command - Function to split the input command line into arguments.
 * @command: The input string (command line).
 *
 * Return: An array of strings (arguments) terminated by NULL.
 */
char **split_command(char *command)
{
	char **argv = malloc(sizeof(char *) * 64);
	char *token;
	int i = 0;

	if (!argv)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}

	token = strtok(command, " ");
	while (token != NULL)
	{
		argv[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
