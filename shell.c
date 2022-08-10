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
 *
 */
void A_sh_loop(void)
{
	char *input;
	char **args;
	int status = 1;

	do {
		A_sh_prompt();

		input = A_sh_line_input(&status);
		args = A_sh_split_str(input);
		if (args)
			status = A_sh_execute(args);

		free(input);
		free(args);

		printf("\n");
	} while (status);

}

/**
 * main - Main Program (A simple Shell - A_sh)
 *
 * Return: int (0 on success)
 */
int main(void)
{

	printf("\n");
	A_sh_loop();


	return (0);
}

