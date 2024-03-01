#include "shell.h"

/**
 * read_buf - reads a buffer from a file descriptor.
 * @info: parameter struct.
 * @buf: buffer to read into.
 * @i: pointer to the current size of buffer.
 *
 * Return: number of bytes read.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * fork_cmd - forks an exec thread to run a command.
 * @info: the parameter & return info struct.
 *
 * Return: void.
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->cmd_status));
		if (WIFEXITED(info->cmd_status))
		{
			info->cmd_status = WEXITSTATUS(info->cmd_status);
			if (info->cmd_status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

/**
 * free_info - Frees fields of the info_t struct.
 * @info: Pointer to the struct whose fields are to be freed.
 * @all: True if freeing all fields.
 *
 * Return: None.
 */
void free_info(info_t *info, int all)
{
	deallocate(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (all)
	{
		if (info->command_buf == NULL)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		deallocate(info->environ);
			info->environ = NULL;
		free_block((void **) info->command_buf);

		if (info->readfd > 2)
			close(info->readfd);

		_putchar(BUF_FLUSH);
	}
}

/**
 * populate_env_list - populates a linked list with environment variables.
 * @info: structure containing the linked list to be populated.
 *
 * Return: 0 on success, 1 on failure
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

/**
 * get_environ - returns a copy of the environment variables as a string array.
 * @info: structure containing environment variables and flags.
 *
 * Return: a string array of environment variables
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->environ_changed)
	{
		info->environ = list_to_strings(info->env);
		info->environ_changed = 0;
	}

	return (info->environ);
}
