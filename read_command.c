#include "shell.h"

/*
 * read_command - function that reads a line of input from user
 * Result is stored in @line
 * Return: line
 */

char *read_command(void)
{
	size_t bsize = 1024; /* buffer size */
	char *line = malloc(bsize);

	if (line == NULL)
	{
		perror("malloc");
		exit(1);
	}

	if (fgets(line, bsize, stdin) == NULL)
	{
		free(line);
		return (NULL);
	}

	return (line);
}
