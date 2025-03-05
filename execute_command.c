#include "shell.h"

/**
 * execute_command - Function that executes and forks a command
 * @argv: input args (command and args)
 * Return: 0 if success and -1 if failure
 */

int execute_command(char **argv)
{
	pid_t pid;
	int status;
	char *command_path;

	if (argv == NULL || argv[0] == NULL)
		return (-1);

	if (strcmp(argv[0], "exit") == 0)
	{/* checks if command is exit and if so exit */
		exit_builtin();
		return (0);
	}
	command_path = is_command_there(argv[0]);/* checks if command exists*/
	pid = fork();/* child process creation */
	if (pid == -1)
	{
		perror("fork");/* forking has failed */
		exit(EXIT_FAILURE);
	}

	else if (pid == 0)
	{
		if (command_path == NULL)/*if command doesnt exist*/
		{
			fprintf(stderr, "./hsh: %s: No such file or directory\n", argv[0]);
			exit(EXIT_FAILURE);/* do not fork*/
		}
		argv[0] = command_path;
		if (execve(argv[0], argv, environ) == -1)
		{
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);/* wait for child process to finish*/
	}
	return (0);
}
