#include "shell.h"

/**
 * A_sh_execute - Execute
 *
 * @args: command
 * @error_count: Error Count
 * @p_name: Program Name
 * @env: Environment Variables
 *
 * Return: int
 */
int A_sh_execute(char **args, int *error_count, char *p_name, char **env)
{
	/*
	* int found
	* int (*builtin)(char **);
	*
	* builtin = get_builtin_function(args[0]);
	*
	* if (builtin)
	*	return (builtin(args));
	*/

	/* args = resolve_file_path(args, *found);*/

	return (A_sh_launch(args, error_count, p_name, env));

}

/**
 * A_sh_launch - Launch a Program
 *
 * @args: Arguments
 * @error_count: Error counts
 * @p_name: Program Name
 * @env: Environment Variables
 *
 * Return: int
 */
int A_sh_launch(char **args, int *error_count, char *p_name, char **env)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == 0)
	{
		if (execve(args[0], args, env) == -1)
		{
			perror(p_name);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("A-sh");
	}
	else
	{
		wait(&status);

		if (status != 0)
			(*error_count)++;
	}

	return (1);
}
