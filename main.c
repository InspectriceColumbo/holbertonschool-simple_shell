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

	while (1)/*main shell loop*/
	{
		display_prompt();

		line = read_command();/*read user input*/
		if (line == NULL)
		{
			break;/*EOF/error, exit the shell */
		}

		if (strlen(line) == 0)
		{
			free(line);/* ignore empty input */
			continue;
		}

		status = execute_command(line);/*execute command*/
		if (status == -1)
		{
			fprintf(stderr, "%s: Command execution failure\n", line);
		}
		free(line);
	}
	return (0);
}
