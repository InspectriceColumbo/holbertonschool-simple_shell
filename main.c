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
		line = trim_spaces(line);/* trims whitespaces before and after*/

		line[strcspn(line, "\n")] = 0;/*strip newline char if present*/
		if (strlen(line) == 0)/*if empty input(no command typed*/
		{
			free(line);/* ignore empty input */
			continue;/*skip to the next iteration */
		}

		execute_command(line);/*execute command*/

		free(line);/* free memory allocated for input line*/
	}
	return (0);
}
