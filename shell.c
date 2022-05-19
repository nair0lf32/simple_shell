#include "shell.h"
/**
*simple_shell - Main function
*Return: Nothing
*/
void simple_shell(void)
{
while (true)
{
printf("$ ");
char *line = read_line();
char **tokens = split_line(line);
if (tokens[0] != NULL)
{
execute(tokens);
}
free(tokens);
free(line);
}
}
/**
*read_line - reads a line from stdin
*Return: Nothing
*/
char *read_line(void)
{
char *line = NULL;
size_t buflen = 0;
errno = 0;
ssize_t strlen = getline(&line, &buflen, stdin);
if (strlen < 0)
{
if (errno)
{
perror("error\n");
}
exit(1);
}
return (line);
}
/**
*split_line - splits a line into tokens
*@line: line to be split
*Return: A NULL terminated array of tokens
*/
char **split_line(char *line)
{
int length = 0;
int capacity = 16;
char **tokens = malloc(capacity * sizeof(char *));
char *delimiters = " \t\r\n";
char *token = strtok(line, delimiters);
while (token != NULL)
{
tokens[length] = token;
length++;
if (length >= capacity)
{
capacity = (int) (capacity * 1.5);
tokens = realloc(tokens, capacity *sizeof(char *));
}
token = strtok(NULL, delimiters);
}
tokens[length] = NULL;
return (tokens);
}
/**
*execute - Executes a command
*@args: command to be executed
*Return: Nothing
*/
void execute(char **args)
{
pid_t child_pid = fork();
if (child_pid == 0)
{
execvp(args[0], args);
perror("shell");
exit(1);
}
else if (child_pid > 0)
{
int status;
do {
waitpid(child_pid, &status, WUNTRACED);
} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
else
{
perror("shell");
}
}
