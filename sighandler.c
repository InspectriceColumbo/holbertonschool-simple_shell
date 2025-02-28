#include "shell.h"
#include <unistd.h>

/**
 * sig_handler - checks if Ctrl C is pressed and if so, exits the shell
 * @sig_num: the signal number, type int
 */

void sig_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
}
