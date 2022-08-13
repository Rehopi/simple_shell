#include "shell.h"

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

	if (str)
	{
		while (str[i])
		{
			printf("%s\n", str[i]);
			i++;
		}
	}

}

/**
 * check_quotes - Checks if c is a quote
 *
 * @c: character
 * @quote: Quote character
 * @quoteopened: boolean (if char is in quote)
 * @quotetoggle: toggle quote
 *
 * @return int
 */
void check_quotes(char c, char quote, int quoteopened, short *quotetoggle)
{
	if (c == quote)
	{
		if (!quoteopened)
			A_sh_toggle(quotetoggle);
	}
}

/**
 * free_memory - Free Allocated Memory
 *
 * @ptr: memory pointer
 */
void free_memory(char **ptr)
{
	int i = 1;

	if (!ptr)
		return;

	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}

	free(ptr);
}