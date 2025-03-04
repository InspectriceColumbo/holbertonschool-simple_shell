#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * split_command - Function to split the input command line into arguments
 * @line: the input command line we need to split
 * Return: An array of strings (arguments) terminated by NULL.
 */
char **split_command(char *line)
{
	char **argv;
	char *token;
	int i = 0;
	int j;

	argv = malloc(sizeof(char *) * 64);/* memory allocation for the args array */

	if (!argv)
	{
		perror("malloc failed");
		exit(1);
	}
	if (line == NULL || strlen(line) == 0)
	{
		argv[0] = NULL;
		return (argv);
	}
	token = strtok(line, " ");/* split args by a space*/

	while (token != NULL)
	{
		argv[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	argv[i] = NULL;

	if (i > 0)/* debugging: check to confirm command and args */
	{
		printf("Command: %s\n", argv[0]);

		for (j = 1; j < i; j++)
		{
			printf("Argument %d: %s\n", j, argv[j]);
		}
	}
	else
		printf("No command entered.\n");
	return (argv);
}
