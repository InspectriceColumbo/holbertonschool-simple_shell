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
			fprintf(stderr, "%s: No such file or directory\n", line);
			return (-1);/*failure code instead of exiting*/
		}
	}

	else/* parent process */
	{
		wait(&status);/* wait for child process to finish*/
	}

	return (0);
}
