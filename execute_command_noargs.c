#include "shell.h"

/**
 * execute_command - Function that executes and forks a command.
 * @line: input line
 * Return: 0 if success and -1 if failure
 */

int execute_command(char *line)
{
	pid_t pid;
	int status;
	char *args[2];/*array to hold command + NULL for execve */

	line[strcspn(line, "\n")] = 0;/*strip newline char if present*/

	/* Preparing the args for execve */
	args[0] = line;
	args[1] = NULL;

	pid = fork();/* child process creation */

	if (pid == -1)
	{
		perror("fork");/* forking has failed */
		return (-1);
	}

	if (pid == 0)/* child process */
	{
		if (execve(line, args, environ) == -1)/*if execve fails print an error*/
		{
			perror(line);
			exit(1);/*Exit child process*/
		}
	}

	else/* parent process */
	{
		wait(&status);/* wait for child process to finish*/
	}

	return (0);
}
