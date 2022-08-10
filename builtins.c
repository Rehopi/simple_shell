#include "shell.h"

int (* const builtin_functions[])(char **) = {
	A_sh_exit, A_sh_echo, A_sh_cd, A_sh_printenv, NULL
};

const char * const builtin_commands[] = {
	"exit", "echo", "cd", "env", NULL
};

builtinfuns_t const builtin_map[] = {
	{"exit", A_sh_exit},
	{"echo", A_sh_echo},
	{"cd", A_sh_cd},
	{"env", A_sh_printenv},
	{NULL, NULL}
};

/**
 * get_builtin_function - Get the builtin function object
 *
 * @cmd: A-sh Command
 *
 * Return: int(*)(char**)
 */
int (*get_builtin_function(char *cmd)) (char **)
{
	int i;

	for (i = 0; builtin_commands[i]; i++)
	{
		if (strcmp(builtin_commands[i], cmd) == 0)
			return (builtin_functions[i]);
	}
	return (NULL);
}

/**
 * get_builtin_function_inmap - Get the builtin function object
 *
 * @cmd: A-sh Command
 *
 * Return: int(*)(char**)
 */
int (*get_builtin_function_inmap(char *cmd)) (char **)
{
	int i;

	for (i = 0; builtin_map[i].command; i++)
	{
		if (strcmp(builtin_map[i].command, cmd) == 0)
			return (builtin_map[i].function);
	}
	return (NULL);
}
