#include "shell.h"

/*
 * read_command - function that reads a line of input from user
 * Result is stored in @line
 * Return: line
 */

char *read_command(void)
{
	size_t size = 0;
	char *line = NULL;

	if (getline(&line, &size, stdin) == -1)
	{
		return (NULL);
	}

	line[strcspn(line, "\n")] = '\0';

	return (line);
}
