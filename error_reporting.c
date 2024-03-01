#include "shell.h"

/**
 * error_putchar - writes a character to the standard error output
 * @c: The character to print
 *
 * Return: 1 on success, -1 on failure with errno set appropriately.
 */
int error_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *error_puts - prints a string to the standard error output
 * @str: the string to be printed
 *
 * Return: void
 */
void error_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		error_putchar(str[i]);
		i++;
	}
}

/**
 * print_d - Prints a decimal (integer) number (base 10).
 * @input: The input.
 * @fd: The file descriptor to write to.
 *
 * Return: Number of characters printed.
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = error_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * print_error - Prints an error message.
 * @info: Parameter and return info struct.
 * @estr: String containing specified error type.
 *
 * Return: 0 if no numbers, -1 on error.
 */
void print_error(info_t *info, char *estr)
{
	error_puts(info->file_name);
	error_puts(": ");
	print_d(info->line_count, STDERR_FILENO);
	error_puts(": ");
	error_puts(info->argv[0]);
	error_puts(": ");
	error_puts(estr);
}
