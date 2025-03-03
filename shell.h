#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>

extern char **environ;/* global environment variable*/

void _puts(char *str);
int _strlen(char *s);
char *_strdup(char *str);
char *concat_all(char *name, char *sep, char *value);
void display_prompt(void);
void sig_handler(int sig_num);
char *read_command(void);
char **split_command(char *line);
int execute_command(char **argv);
char **splitstring(char *str, const char *delim);
void execute(char **argv);
char **split_command(char *line);
char *is_command_there(char *command);
void exit_builtin(void);
void env_builtin(void);

#endif
