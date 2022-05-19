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
size_t buffer_size = 0;
errno = 0;
ssize_t strlen = getline(&line, &buffer_size, stdin);
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
int memsize = 1024;
char **tokens = malloc(memsize * sizeof(char *));
char *delimiters = " \t\r\n";
char *token = strtok(line, delimiters);
while (token != NULL)
{
//handle EOF
if (token == EOF || token == '\n')
{
tokens[length] = '\0';
return (tokens);
} 
else 
{
tokens[length] = token;
}
length++;
// handle memory allocation
if (length >= memsize)
{
memsize = (int) (memsize * 2);
tokens = realloc(tokens, memsize *sizeof(char *));
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
perror("error\n");
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
perror("error\n");
}
}
