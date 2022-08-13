#include "shell.h"
#include <string.h>
/**
 * _builtin_ - find the command inside path
 * @path: double pointer to char array input
 * @cmd: pointer to char array input
 * Return: 1 if function is builtin or 0 if function is no builtin
 */
int _builtin_(char **path, char *cmd)
{
	int i = 0;

	for (i = 0; path[i]; i++)
	{
		if (strcmp(cmd, path[i]) == 0)
			return (1);
	}
	return (0);
}
