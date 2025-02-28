#include "shell.h"

/**
 * trim_space - trims whitespaces before and after a string
 * @str: input string
 * Return: new string without whitespaces
 */

char *trim_space(char *str)
{
	while (isspace(*str))/* trims spaces before str */
		str++;

	if (*str == 0)/* if str empty after trimming */
		return (str);

	char *end = str + strlen(str) - 1;/* finds end of str*/

	while (end > str && isspace(*end))/* now trims spaces after str*/
		end--;

	*(end + 1) = '\0';/* null-terminate str after trim*/

	return (str);
}
