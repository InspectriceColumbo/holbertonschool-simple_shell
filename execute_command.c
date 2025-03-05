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

	command_path = is_command_there(argv[0]);/* checks if command exists*/

	if (command_path == NULL)/*if command doesnt exist*/
	{
		fprintf(stderr, "./hsh: %s: No such file or directory\n", argv[0]);
		return (-1);/* do not fork*/
	}

	pid = fork();/* child process creation */

	if (pid == -1)
	{
		perror("fork");/* forking has failed */
		exit(EXIT_FAILURE);
	}

	if (pid == 0)/* child process */
	{
		if (execve(command_path, argv, environ) == -1)
		{
			fprintf(stderr, "./hsh: %s: Execution failure\n", command_path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);/* wait for child process to finish*/
	}
	return (0);
}
