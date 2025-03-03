#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

/**
 * is_command_there - Checks if @command exists PATH directories
 * @command: the command to check
 * Return: full path to the command if it exists, NULL if not
 */

char *is_command_there(char *command)
{
	char *path = getenv("PATH");
	char *directory;
	char *fullpath;
	struct stat fileinfo;

	if (command == NULL || path == NULL)
		return (NULL);

	if (command[0] == '/' || command[0] == '.')/* if command has slash */
/* it is absolute, if ./ it is relative, in both cases don't check PATH */
	{
		if (stat(command, &fileinfo) == 0)/* checks if file exist*/
			return (command);/* if so returns the command*/
		else
			return (NULL);/* return NULL if command doesnt exist */
	}
	directory = strtok(path, ":");/*split PATH by ":" and check each dir*/

	while (directory != NULL)
	{
		fullpath = malloc(strlen(directory) + strlen(command) + 2);/*for '/' & '\0'*/

		if (fullpath == NULL)
		{
			perror("malloc failed");
			exit(1);
		}
		sprintf(fullpath, "%s/%s", directory, command);/*create full path 2 command*/

		if (stat(fullpath, &fileinfo) == 0)/* checks if command exists in dir*/
		{
			return (fullpath);/* command found*/
		}

		free(fullpath);/* free memory and try next directory*/
		directory = strtok(NULL, ":");
	}
	return (NULL);/* command not found in any directory*/
}
