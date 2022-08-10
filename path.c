#include "shell.h"

/**
 * A_sh_plane_split_str - Split String by DELIM
 *
 * @str: String to split
 * @delim: Delimiter
 *
 * Return: char** (Splitted String)
 */
char **A_sh_plane_split_str(char *str, char delim)
{
	int buffersize = A_BUF_SIZE, abuffersize = A_BUF_SIZE;
	int i = 0, j = 0, k = 0;
	char *arg, **args;

	if (!str || !str[0])
		return (NULL);

	args = malloc(sizeof(char *) * buffersize);
	arg = malloc(sizeof(char) * abuffersize);
	if (!args || !arg)
		return (NULL);

	while (str[i])
	{
		if (str[i] == delim)
		{
			arg[k] = '\0';
			args[j++] = arg;

			args = check_and_realloc(
				args, &buffersize, j, sizeof(char *), A_BUF_SIZE
			);
			if (!args)
				return (NULL);
			abuffersize = A_BUF_SIZE;
			k = 0;
			arg = malloc(sizeof(char) * abuffersize);
			if (!arg)
				return (NULL);
		}
		else
		{
			arg[k++] = str[i];
			arg = check_and_realloc(arg, &abuffersize, k, sizeof(char), A_BUF_SIZE);
			if (!arg)
				return (NULL);
		}
		i++;
	}
	return (cleanup(arg, k, args, j));
}

/**
 * get_file - Get the file object
 *
 * @cmd: Command
 *
 * Return: char*
 */
char *get_file(char *cmd)
{
	char *path = malloc(sizeof(char) * 1024);
	char **paths;
	int i;

	paths = A_sh_plane_split_str(getenv("PATH"), PATHDELIM);

	for (i = 0; paths[i]; i++)
	{
		snprintf(path, (sizeof(char) * 1024), "%s/%s", paths[i], cmd);
		if (access(path, F_OK) == 0)
		{
			return (path);
		}
	}

	return (NULL);
}

/**
 * resolve_file_path - Resolve path to commands
 *
 * @args: A-sh Arguments
 *
 * Return: char**
 */
char **resolve_file_path(char **args)
{
	char *fullpath, *cmd;

	cmd = args[0];

	if (!strchr(cmd, PATHSEP))
	{
		fullpath = get_file(cmd);

		if (fullpath)
		{
			args[0] = fullpath;
			free(cmd);
		}
	}
	return (args);
}
