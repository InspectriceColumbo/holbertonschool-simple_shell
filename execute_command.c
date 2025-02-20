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
        return 1;
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

    return 0;
}
