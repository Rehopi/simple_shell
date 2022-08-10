#include "shell.h"

/**
 * A_sh_execute - Execute
 *
 * @args: command
 *
 * Return: int
 */
int A_sh_execute(char **args)
{

	int (*builtin)(char **);

	builtin = get_builtin_function(args[0]);

	if (builtin)
		return (builtin(args));

	args = resolve_file_path(args);

	return (A_sh_launch(args));

}

/**
 * A_sh_launch - Launch a Program
 *
 * @args: Arguments
 *
 * Return: int
 */
int A_sh_launch(char **args)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == 0)
	{
		if (execve(args[0], args, __environ) == -1)
		{
			perror("Error");
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
	}

	return (1);
}
