#ifndef SHELL_H_
#define SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#define bufsize 1024

void _exit_(char *line);
void _env_(char **env);
void _printnumber_(int n);
void _freestrs_(char **str);
void _ts_handler_(char *line);
void _execute_(char **array_token);
void _echo_(char *str);
void _strcat_(char *dest, char *src);
void _strcpy_(char *dest, char *src);
void _notfound_(char *av, int i, char *array_token);
int _builtin_(char **path, char *cmd);
char *_findpath_(char **env);

#define BUFFER_SIZE 1024

char *A_sh_line_input(char *prompt);
char **A_sh_split_str(char *str);
void A_sh_print(char **str);
void reallocate(int j, int buffersize, char *arv);
int A_sh_execute(char **args);

#endif
