#include "shell.h"


/**
 * A_sh_line_input - Readline from stdin
 *
 * Return: char* (read string)
 */
char *A_sh_line_input()
{
	char *buffer;
	int c, i = 0, bufsize = BUFFER_SIZE;
	short quoteopened = 0, squoteopened = 0;

	buffer = malloc(sizeof(char) * bufsize);
	if (!buffer)
		return (NULL);

	do {
		c = getchar();

		if (c == EOF)
		{
			buffer[i] = '\0';
			return (buffer);
		}

		if (c == '\n')
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
		escape_quote(c, &quoteopened, &squoteopened);

		i++;
		buffer = check_and_realloc(buffer, &bufsize, i, sizeof(char), BUFFER_SIZE);
		if (!buffer)
			return (NULL);

	} while (1);
}
