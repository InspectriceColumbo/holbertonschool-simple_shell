#include "shell.h"

/**
 * display_prompt - function that displays our prompt if stdin is a terminal
 * Return: nothing (void)
 */

void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		printf("c$");
		fflush(stdout);
	}
}
