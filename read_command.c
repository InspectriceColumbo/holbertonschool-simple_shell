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
	ssize_t len = getline(&line, &bsize, stdin);/* read command from stdin */

	if (len == -1)/* EOF or error */
	{
		if (line == NULL)/* if no input is read */
		{
			return (NULL);
		}
		else
		{
			if (isatty(STDIN_FILENO))/* if interactive mode */
			{
				printf("\n");
			}
			free(line);
			return (NULL);/* return NULL on error */
		}
	}

	return (line);/* return the command if no error */
}
