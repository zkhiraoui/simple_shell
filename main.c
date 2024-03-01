/**
 * Introduction
 *		Set up initial variables and data structures.
 *		Parse command line arguments and open script file if provided.
 *		Populate environment variables list.
 *		Read history file, if it exists.
 *		Enter main shell loop (run_command function), which will run until an
 *				error or the exit command is entered.
 *		Cleanup and free memory, including writing history to file if
 *				it was modified during the session.
 *		Exit program with success or failure cmd_status code.
*/

#include "shell.h"

/**
 * main - Entry point.
 * @ac: Argument count.
 * @av: Argument vector.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				error_puts(av[0]);
				error_puts(": 0: Can't open ");
				error_puts(av[1]);
				error_putchar('\n');
				error_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	run_command(info, av);
	return (EXIT_SUCCESS);
}
