#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

/**
 * main - Entry point of our shell program
 *
 * Return: Always 0 (success).
 */

int main(void)
{
	char *line;
	char **argv;

	signal(SIGINT, sig_handler);/* signal handler for ctrl+c*/

	while (1)/*main shell loop*/
	{
		if (isatty(STDIN_FILENO))/* only display prompt if interactive mode */
		{
			display_prompt();
		}

		line = read_command();/*read user input*/

		if (line == NULL)/*Checking for EOF or error */
		{
			free(line);
			break;/*Exit the shell on EOF*/
		}

		line[strcspn(line, "\n")] = 0;/*strip newline char if present*/

		if (strlen(line) == 0)/*if empty input(no command typed*/
		{
			free(line);/* ignore empty input */
			continue;/*skip to the next iteration */
		}

		argv = split_command(line);/* splits command line into args*/

		execute_command(argv);/*execute command using argv*/

		free(argv);/* free memory allocated for agrs*/
		free(line);/* free memory allocated for input line*/
	}

	return (0);
}
