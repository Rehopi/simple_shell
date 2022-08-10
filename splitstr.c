#include "shell.h"

/**
 * cleanup - A completely useless function
 * forced to be written inorder to pass stupid betty style
 *
 * @arg: Arg
 * @k: k
 * @args: Args
 * @j: J
 *
 * Return: args
 */
char **cleanup(char *arg, int k, char **args, int j)
{
	arg[k] = '\0';
	args[j] = arg;
	args[j + 1] = NULL;
	return (args);
}

/**
 * check_and_realloc - Check to reallocate memory
 *
 * @buf: Buffer
 * @bufsize: Current Buffer size
 * @i: Compare buffer size
 * @size: Size of a unit datatype
 * @incby: Increase buffersize by
 *
 * Return: void*
 */
void *check_and_realloc(void *buf, int *bufsize, int i, size_t size, int incby)
{
	if (i >= (*bufsize))
	{
		*bufsize += incby;

		buf = realloc(buf, size * (*bufsize));
		if (!buf)
			return (NULL);
	}

	return (buf);
}

/**
 * escape_quote - Check if to escape Quote characters
 *
 * @c: Character
 * @insidequote: double quote status
 * @insideSquote: single quote statusror
 *
 * Return: int
 */
int escape_quote(char c, short *insidequote, short *insideSquote)
{
	if (c == '"')
	{
		if (!(*insideSquote))
		{
			A_sh_toggle(insidequote);
			return (1);
		}
	}

	else if (c == '\'')
	{
		if (!(*insidequote))
		{
			A_sh_toggle(insideSquote);
			return (1);
		}
	}

	return (0);
}

/**
 * iswhitespace - Check if a character is whitespace
 *
 * @c: Character
 *
 * Return: int
 */
int iswhitespace(char c)
{
	int i;
	char *spacechars = " \t";

	for (i = 0; spacechars[i]; i++)
	{
		if (c == spacechars[i])
			return (1);
	}

	return (0);
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
	int buffersize = A_BUF_SIZE, abuffersize = A_BUF_SIZE;
	int i = 0, j = 0, k = 0;
	short lastisspace, insidequote = 0, insideSquote = 0;
	char *arg, **args;

	if (!str || !str[0])
		return (NULL);
	lastisspace = iswhitespace(*str) ? 1 : 0;
	args = malloc(sizeof(char *) * buffersize);
	arg = malloc(sizeof(char) * abuffersize);
	while (str[i])
	{
		if ((str[i] == ' ' || str[i] == '\t') && !insidequote && !insideSquote)
		{
			if (!lastisspace)
			{
				arg[k] = '\0';
				args[j++] = arg;
				args = check_and_realloc(args, &buffersize, j, sizeof(char *), A_BUF_SIZE);
				if (!args)
					return (NULL);
				abuffersize = A_BUF_SIZE;
				k = 0;
				arg = malloc(sizeof(char) * abuffersize);
				if (!arg)
					return (NULL);
				lastisspace = 1;
			}
		}
		else if (!escape_quote(str[i], &insidequote, &insideSquote))
		{
			arg[k++] = str[i];
			arg = check_and_realloc(arg, &abuffersize, k, sizeof(char), A_BUF_SIZE);
			if (!arg)
				return (NULL);
			lastisspace = 0;
		}
		i++;
	}
	return (cleanup(arg, k, args, j));
}


