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

		if (i >= 64)/* if array size not enough dynamically resize it*/
		{
			argv = _realloc(argv, sizeof(char *) * (i + 1));

			if (!argv)/* check if realloc failed (returned NULL)*/
			{
				perror("realloc failed");
				exit(1);
			}
		}
	}
	argv[i] = NULL;

	return (argv);
}
