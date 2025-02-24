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
	char *args[100];/* array holding command and potential args*/

	char *token = strtok(line, " ");
	int i = 0;

	while (token != NULL)
	{
		args[i] = token;
		token = strtok(NULL, " ");
		i++;
	}

	args[i] = NULL; /* nullterminating the args list */

	pid = fork();/* child process creation */
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}

	if (pid == 0)/* child process */
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror("execve has failed");
			exit(1);
		}
	}

	else/* parent process */
	{
		wait(&status);
	}

	return (0);
}
