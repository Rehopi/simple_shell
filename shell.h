#ifndef SHELL_H_
#define SHELL_H_

#ifdef _WIN32
#define PATHDELIM ';'
#define PATHSEP '\\'
#else
#define PATHDELIM ':'
#define PATHSEP '/'
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#define BUFFER_SIZE 512
#define A_BUF_SIZE 64

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



char *A_sh_line_input(int *iseof);
char **A_sh_split_str(char *str);
char **A_sh_plane_split_str(char *str, char delim);
void A_sh_print(char **str);
void A_sh_prompt(void);
int A_sh_execute(char **args);
int A_sh_launch(char **args);
void A_sh_toggle(short *value);

void print_error(char *command, char *program_name, int error_count)
void *check_and_realloc(void *, int *, int, size_t, int);
int iswhitespace(char c);
int escape_quote(char c, short *insidequote, short *insideSquote);
void check_quotes(char c, char quote, int quoteopened, short *quotetoggle);
char **cleanup(char *arg, int k, char **args, int j);
void free_memory(char **ptr);
char **resolve_file_path(char **args);

/* A_sh Builtins */
int A_sh_exit(char **args);
int A_sh_echo(char **args);
int A_sh_cd(char **args);
int A_sh_printenv(char **args);
int (*get_builtin_function(char *cmd)) (char **);
int (*get_builtin_function_inmap(char *cmd)) (char **);

/* A_sh Variable for all Builtin Commands */
extern  const char * const builtin_commands[];

/* A_sh Variable for all Builtin Functions */
extern int (* const builtin_functions[]) (char **);


/**
 * struct builtin_command_function_map - As Name implies
 * A_sh Struct for Builtin Command-Function map
 *
 * @command: Builtin Command
 * @function: Mapped function
 */
typedef struct builtin_command_function_map
{
	char *command;
	int (*function)(char **);
} builtinfuns_t;

/* A_sh Array of Builtin Command-Function map */
extern builtinfuns_t const builtin_map[];

#endif
