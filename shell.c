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

int A_sh_execute(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();

	if (pid == 0)	// Child Process
	{
		if (execve(args[0], args, __environ) == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0) // Forking Error
	{
		perror("A-sh");
	}
	else	// Parent Process
	{
		wpid = wait(&status);
	}

	return 1;

}

void A_sh_loop(void)
{
	char *input;
	char **args;
	int status;

	do {
		printf("\033[1;33m┌───(\033[1;30mUser @ A-sh\033[1;33m)-[\033[1;35mCurrent Working Dir\033[1;33m]\n");
		printf("└──$\033[0m ");

		input = A_sh_line_input("");
		if (strcmp(input, "exit") == 0)
			break;
		args = A_sh_split_str(input);
		status = A_sh_execute(args);

		free(input);
		free(args);

		printf("\n");
	} while (status);

}

/**
 * A_sh_toggle - Toggle a boolean value
 *
 * @value: Pointer to a short value
 */
void A_sh_toggle(short *value)
{
	if (*value)
		*value = 0;
	else
		*value = 1;
}

/**
 * A_sh_print - Prints an array of strings
 *
 * @str: Pointer to an array of strings to print
 */
void A_sh_print(char **str)
{
	int i = 0;

	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}

}

/**
 * A_sh_split_str - Split String by whitespace
 *
 * @str: String to split
 *
 * Return: char** (Splitted String)
 */
char **A_sh_split_str(char *str)
{
	int buffersize = 64, i = 0, j = 0, k = 0, abuffersize = 64;
	short lastisspace = 0, insidequote = 0, insideSquote = 0;
	char **args;
	char *arg;

	args = malloc(sizeof(char *) * buffersize);
	arg = malloc(sizeof(char) * abuffersize);

	while (str[i])
	{
		if ((str[i] == ' ' || str[i] == '\t') && !insidequote && !insideSquote)
		{
			i++;
			if (lastisspace)
				continue;
			arg[k] = '\0';
			args[j] = arg;
			j++;

			if (j >= buffersize)
			{
				buffersize += 64;
				args = realloc(args, sizeof(char *) * buffersize);
			}

			abuffersize = 64;
			k = 0;
			arg = malloc(sizeof(char) * abuffersize);
			lastisspace = 1;

			continue;

		}
		else if (str[i] == '"')
		{
			if (!insideSquote)
			{
				A_sh_toggle(&insidequote);
				i++;
				continue;
			}

		}
		else if (str[i] == '\'')
		{
			if (!insidequote)
			{
				A_sh_toggle(&insideSquote);
				i++;
				continue;
			}

		}
		arg[k] = str[i];
		k++;

		if (k >= abuffersize)
		{
			abuffersize += 64;
			arg = realloc(arg, abuffersize);
		}
		lastisspace = 0;
		i++;
	}

	arg[k] = '\0';
	args[j] = arg;
	args[j + 1] = NULL;

	return (args);
}

/**
 * A_sh_line_input - Readline from stdin
 *
 * @prompt: Prompt to display
 *
 * Return: char* (read string)
 */
char *A_sh_line_input(char *prompt)
{
	char *buffer;
	int c, i = 0, buffersize = BUFFER_SIZE;
	short quoteopened = 0, squoteopened = 0;

	printf("%s", prompt);

	buffer = malloc(sizeof(char) * buffersize);
	if (!buffer)
		return (NULL);

	do {
		c = getchar();

		if (c == EOF || c == '\n')
		{
			if (quoteopened)
				printf("dquote>");
			else if (squoteopened)
				printf("squote>");
			else
			{
				buffer[i] = '\0';
				return (buffer);
			}
		}

		buffer[i] = c;

		if (c == '"')
		{
			if (!squoteopened)
				A_sh_toggle(&quoteopened);
		}

		else if (c == '\'')
		{
			if (!quoteopened)
				A_sh_toggle(&squoteopened);
		}

		i++;

		if (i >= buffersize)
		{
			buffersize += BUFFER_SIZE;
			buffer = realloc(buffer, buffersize);
			if (!buffer)
			{
				return (NULL);
			}
		}

	} while (1);
}

/**
 * main - Main Program (A simple Shell - A_sh)
 *
 * @ac: Program Argument Count
 * @av: Program Arguments
 * @env: Inherited Environment Variables
 *
 * Return: int (0 on success)
 */
int main(int ac, char **av, char **env)
{

	// read

	// printf("Command Line Args: %d\n\n", ac);
	// A_sh_print(av);
	// exit(0);


	// printf("╔ ═ ╗ ╚ ╝  ┌─┐┌─┼─┘ ║\n");

	printf("\n");
	A_sh_loop();


	return (0);
}

