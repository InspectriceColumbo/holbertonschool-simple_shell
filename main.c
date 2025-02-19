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
	char *line;
	char **argv;
	int status;

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
