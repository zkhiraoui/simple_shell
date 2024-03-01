#include "shell.h"

/**
 * find_built_in - finds a built_in command in the shell's built_in table.
 * @info: the parameter & return info struct.
 *
 * Return: -1 if built_in not found,
 *				0 if built_in executed successfully,
 *				1 if built_in found but not successful,
 *				-2 if built_in signals exit().
 */
int find_built_in(info_t *info)
{
	int i, built_in_ret = -1;
	built_in_table built_intbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; built_intbl[i].type; i++)
		if (string_strcmp(info->argv[0], built_intbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = built_intbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * check_chain - Checks if we should continue chaining based on last cmd_status.
 *
 * @info: Pointer to the parameter struct.
 * @buf: The char buffer.
 * @pos: Address of current position in buf.
 * @i: Starting position in buf.
 * @len: Length of buf.
 *
 * Return: void.
 */
void check_chain(info_t *info, char *buf, size_t *pos, size_t i, size_t len)
{
	size_t j = *pos;

	if (info->buf_format == CMD_AND)
	{
		if (info->cmd_status)
		{
			buf[i] = '\0';
			j = len;
		}
	}

	if (info->buf_format == CMD_OR)
	{
		if (!info->cmd_status)
		{
			buf[i] = '\0';
			j = len;
		}
	}

	*pos = j;
}

/**
 * _myenv - prints the current environment using info_t structure argument.
 * @info:  structure containing the environment variables.
 *
 * Return: 0 on success, 1 on failure
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _mysetenv -Initialize a new environment variable or modify an existing one.
 * @info: structure containing potential arguments and environment variables.
 *
 *  Return: 0 on success, 1 on failure
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		error_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable.
 * @info: structure containing potential arguments and environment variables.
 *  Return: 0 on success, 1 on failure
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		error_puts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}
