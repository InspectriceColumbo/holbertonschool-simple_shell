#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * main - Entry point of our shell program
 *
 * Return: Always 0 (success).
 */

int main(void)
{
	char *line; /* string - user's command input */
	int status; /* stores the status code returned by exec the command */

	while (1)
	{
		display_prompt();

		line = read_command();

		if (line == NULL)
		{
			free(line);
			break;
		}

		if (strlen(line) == 0)
		{
			free(line);
			continue;
		}

		status = execute_command(line);

		if (status == 0)
		{
			fprintf(stderr, "%s: Command execution failure\n", line);
		}

		free(line);
	}
	return (0);
}

#include "shell.h"

/*
 * read_command - function that reads a line of input from user
 * Result is stored in @line
 * Return: line
 */

char *read_command(void)
{
	size_t size = 0;
	char *line = NULL;

	if (getline(&line, &size, stdin) == -1)
	{
		return (NULL);
	}

	line[strcspn(line, "\n")] = '\0';

	return (line);
}

#include "shell.h"

/**
 * display_prompt - function that displays our basic prompt
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

	char *token = strtok(line, " ");
	char *args[100];
	int i = 0;

	while (token != NULL)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("execvp");
			exit(1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}

	return (0);
}
