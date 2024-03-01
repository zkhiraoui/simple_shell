/**
 * Introduction
 *		set_info: Initializes the info_t struct with information about the shell
 *			and its arguments. It also processes any command-line arguments
 *			passed to the shell.
 *		get_input: Reads user input from standard input and buffers chained
 *			commands. It checks if there are multiple commands chained together
 *			with && or || and buffers them separately.
 *			The function returns the number of bytes read.
 */

#include "shell.h"

/**
 * set_info - initialize the info_t struct.
 * @info: pointer to the struct to be initialized.
 * @av: argument vector that contains the arguments passed to the shell.
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->file_name = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = string_dupy(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * get_input - reads user input from standard input and
 *          buffers chained commands.
 * @info: parameter struct.
 *
 * Return: number of bytes read.
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->buf_format = CMD_NORM;
		}

		*buf_p = p;
		return (string_strlen(p));
	}

	*buf_p = buf;
	return (r);
}
