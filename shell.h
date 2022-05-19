#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

void simple_shell(void);
char* read_line();
char** split_line(char *line);
void execute(char **args);

#endif /* SHELL_H */
