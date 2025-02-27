#include "shell.h"
#include <unistd.h>

/**
 * sig_handler - checks if Ctrl C is pressed
 * @sig_num: int
 */

void sig_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		write(STDOUT_FILENO, "\nc$ ", 4);  /* Prints prompt after Ctrl+C */
	}
}
