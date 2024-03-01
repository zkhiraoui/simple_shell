#include "shell.h"

/**
 * _mycd - changes the current directory
 * @info: a pointer to the info_t structure
 *
 *  Return: 0 on success, otherwise -1
 */
int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (string_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		error_puts(info->argv[1]), error_putchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhistory - prints the history of commands
 * @info: pointer to struct containing command information
 *
 *  Return: always returns 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * _myexit - handles the exit built_in command
 * @info: pointer to info struct
 *
 * Return: -2 on success, 1 on error
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->cmd_status = 2;
			print_error(info, "Illegal number: ");
			error_puts(info->argv[1]);
			error_putchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * exit_strncat - Concatenates two strings up to a certain number of bytes.
 * @dest: The destination string.
 * @src: The source string.
 * @n: The maximum number of bytes to be concatenated.
 *
 * Return: The concatenated string.
 */
char *exit_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}

	j = 0;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	if (j < n)
	{
		dest[i] = '\0';
	}

	return (s);
}
