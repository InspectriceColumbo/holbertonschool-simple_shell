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
	int status;

	char *path = getenv("PATH");
	{
		if (path != NULL)
		{
			printf("PATH: %s\n", path);
		}
		else
		{
			printf("PATH environment var is not set.\n");
		}
	}

	while (1)
	{
		display_prompt();

		line = read_command();

		if (line == NULL)
		{
			free(line);
			break;
		}

		line[strcspn(line, "\n")] = 0; /*strip newline char if present */

		if (strlen(line) == 0)
		{
			free(line);
			continue;
		}

		status = execute_command(line);

		if (status == 0)
		{
			fprintf(stderr, "%s: Command execution failure\n", line);
		}

		free(line);
	}
	return (0);
}
