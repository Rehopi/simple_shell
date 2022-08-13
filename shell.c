/*************************************************
 * ALX Team project 2 - A Shell Program (The A-sh)
 * Team:
 *      - Samuel Okechukwu
 *      - Warith Adeoti
 * Date
 *      - July 27, 2022
 ************************************************/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include <string.h>
#include <wait.h>


/**
 * A_sh_prompt - Prints a prompt
 */
void A_sh_prompt(void)
{
	char *cwd = NULL;

	printf(
		"\033[1;33m┌───(\033[1;30m%s @ A-sh\033[1;33m)-",
		getenv("USER")
	);
	printf("[\033[1;35m%s\033[1;33m]\n", getcwd(cwd, sizeof(char) * 100));
	printf("└─$\033[0m ");

	free(cwd);
}

/**
 * A_sh_loop - Main Program Loop
 * @p_name: Program Name
 */
void A_sh_loop(char *p_name)
{
	char *input;
	char **args = NULL;
	int status = 1;
	int error_count = 1;
	int is_interactive = 1;

	do {

		if (isatty(fileno(stdin)))
			A_sh_prompt();
		else
			is_interactive = 0;

		input = A_sh_line_input();

		if (1)
		{

			if (input[0])
			{
				args = malloc(sizeof(char *) * 2);
				args[0] = input;
				args[1] = NULL;
			}
			else
			{
				status = 0;
			}
		}
		else
		{
			args = A_sh_split_str(input);
		}
		if (args)
			status = A_sh_execute(args, &error_count, p_name);

		free(input);
		free_memory(args);
	} while (status && is_interactive);

}

/**
 * main - Main Program (A simple Shell - A_sh)
 *
 * @ac: Argument Count
 * @av: Program Arguments
 *
 * Return: int (0 on success)
 */
int main(int ac, char **av)
{
	char **args;
	int error = 0;

	if (ac > 1)
	{
		args = malloc(sizeof(char *) * (ac + 1));
		memcpy(args, av, sizeof(char *) * ac);
		args[ac] = NULL;
		A_sh_print(args + 1);

		A_sh_execute(args + 1, &error, av[0]);
		return (0);
	}

	A_sh_loop(av[0]);


	return (0);
}

