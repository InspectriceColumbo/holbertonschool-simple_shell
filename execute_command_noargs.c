#include "shell.h"

/**
 * execute_command - Function that executes and forks a command.
 * @line: input line
 * Return: 1 if success and 0 if failure
 */

int execute_command(char *line)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}

	else if (pid == 0)
	{
		char *args[2];

		args[0] = line;
		args[1] = NULL;

		if (execvp(args[0], args) == -1)
		{
			perror("execvp failure");
			exit(1);
		}
	}

	else
	{
		waitpid(pid, &status, 0);
	}

	return (0);
}
