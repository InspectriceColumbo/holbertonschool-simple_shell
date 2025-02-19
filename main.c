#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * main - Entry point of our shell program
 *
 * Return: Always 0 (success).
 */

int main(void)
{
	char *line; /* string - user's command input */
	char **argv; /* not used atm, will store split command arguments */
	int status; /* stores the status code returned by exec the command */

	while (1)
	{
		display_prompt();

		line = read_command();
		
		if (line == NULL)
		{
			free(line);
			break;
		}

		if (strlen(line) == 0)
		{
			free(line);
			continue;
		}

		argv = split_command(line);

		status = execute_command(argv);

		if (status == 0)
		{
			fprintf(stderr, "%s: Command execution failure\n", argv[0]);
		}
		
		free(argv);
		free(line);
	}
	return (0);
}
