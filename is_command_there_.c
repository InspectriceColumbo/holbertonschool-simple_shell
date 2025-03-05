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
	char *path_copy, *directory, *fullpath;
	struct stat fileinfo;

	if (path == NULL)
		return (NULL);

	path_copy = strdup(path);/*duplicate PATH string to prevent strtok pb*/

	if (command[0] == '/' || command[0] == '.')/*check for abs/rel path*/
	{
		if (stat(command, &fileinfo) == 0)/* checks if file exist*/
			return (command);/* if so returns the command*/
		else
			return (NULL);/* return NULL if command doesnt exist */
	}
	directory = strtok(path_copy, ":");/*using strtok on copy so that the */
	/* original PATH string remains intact for future calls */

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
			free(path_copy);/* frees the copied PATH string before returning*/
			return (fullpath);/* command found, return full path*/
		}
		free(fullpath);/* free memory and try next directory*/
		directory = strtok(NULL, ":");
	}
	free(path_copy);/* frees copied PATH string if no command found*/
	return (NULL);/* command not found in any directory*/
}
