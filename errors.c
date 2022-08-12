#include "shell.h"

/**
 * print_error - prints error messages to standard error
 * @command: pointer to struct of variables
 * @program_name: message to print
 *
 * Return: void 
*/
void print_error(char *command, char *program_name, int error_count)
{
	fprintf(stderr,"%s: %d: %s: not found", program_name, error_count, command);
}