/**
 * Introduction: This function reads input from the user or a script file,
 * 				parses the input into tokens, and executes
 * 				the appropriate command
*/

#include "shell.h"

/**
 * run_command - main shell loop.
 * @info: Parameter & return info struct.
 * @av: Argument vector from main().
 *
 * Return: 0 on success, 1 on error, or error code.
 */
int run_command(info_t *info, char **av)
{
	ssize_t r = 0;
	int built_in_ret = 0;

	while (r != -1 && built_in_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		error_putchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			built_in_ret = find_built_in(info);
			if (built_in_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->cmd_status)
		exit(info->cmd_status);
	if (built_in_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->cmd_status);
		exit(info->err_num);
	}
	return (built_in_ret);
}
