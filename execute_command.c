#include "shell.h"

/**
 * execute_command - Function that executes and forks a command.
 * @argv: input args (command and args)
 * Return: 0 if success and -1 if failure
 */

int execute_command(char **argv)
{
	pid_t pid;
	int status;

	if (argv == NULL || argv[0] == NULL)
	{
		return (-1);
	}

	pid = fork();/* child process creation */

	if (pid == -1)
	{
		perror("fork");/* forking has failed */
		return (-1);
	}

	if (pid == 0)/* child process */
	{
		if (execve(argv[0], argv, environ) == -1)/*if execve fails print an error*/
		{
			fprintf(stderr, "./hsh: %s: No such file or directory\n", argv[0]);
			return (-1);/*failure code instead of exiting*/
		}
	}

	else/* parent process */
	{
		wait(&status);/* wait for child process to finish*/
	}

	return (0);
}
