#include "shell.h"

/*
 * read_command - function that reads a line of input from user
 * Result is stored in @line
 * Return: line
 */

char *read_command(void)
{
	size_t bsize = 0; /* getline will dinamically allocate memory */
	char *line = NULL;

	/*Read the command from stdin */
	if (getline(&line, &bsize, stdin) == -1)
	{
		free(line);/* End of file condition (Ctrl+D) or error */
		return (NULL);
	}

	return (line);
}
