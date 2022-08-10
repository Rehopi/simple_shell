#include "shell.h"

/**
 * A_sh_exit - Exit A-sh
 *
 * @args: A-sh Argument
 *
 * Return: int
 */
int A_sh_exit(char **args)
{
	if (!args[1])
		return (0);

	fprintf(stderr, "A-sh: expected no argument to \"exit\"\n");

	return (1);
}

/**
 * A_sh_echo - Prints Argument and newline
 *
 * @args: A-sh Argument
 *
 * Return: int
 */
int A_sh_echo(char **args)
{
	int i;

	if (args)
	{
		printf("%s", args[1]);
		for (i = 2; args[i]; i++)
			printf(" %s", args[i]);
	}
	printf("\n");

	return (1);
}

/**
 * A_sh_cd - Change current working directory
 *
 * @args: A-sh Argument
 *
 * Return: int
 */
int A_sh_cd(char **args)
{
	if (args[1] == NULL)
		fprintf(stderr, "A-sh: expected argument to \"cd\"\n");
	else
	{
		if (chdir(args[1]) != 0)
			perror("A-sh");
	}

	return (1);
}

/**
 * A_sh_printenv - Print enviroment variable
 *
 * @args: A-sh Argument
 *
 * Return: int
 */
int A_sh_printenv(char **args)
{
	char *env;

	if (args[1] == NULL)
		A_sh_print(__environ);
	else
	{
		env = getenv(args[1]);
		if (!env)
		{
			fprintf(stderr, "A-sh: Unknown env key (%s)\n", args[1]);
		}

		printf("%s\n", env);
	}

	return (1);
}
