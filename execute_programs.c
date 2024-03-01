#include "shell.h"

/**
 * is_known_cmd - Determines if a file is an executable command.
 * @info: The info struct.
 * @path: Path to the file.
 *
 * Return: 1 if true, 0 otherwise.
 */
int is_known_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * find_path - Finds this cmd in the PATH string.
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @cmd: The cmd to find.
 *
 * Return: Full path of cmd if found or NULL.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((string_strlen(cmd) > 2) && string_prefix_equal(cmd, "./"))
	{
		if (is_known_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = copy_chars(pathstr, curr_pos, i);
			if (!*path)
				string_strcat(path, cmd);
			else
			{
				string_strcat(path, "/");
				string_strcat(path, cmd);
			}
			if (is_known_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * find_cmd - finds a command in PATH.
 * @info: parameter & return info struct.
 *
 * Return: void.
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;

	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);

	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=") ||
		     info->argv[0][0] == '/') && is_known_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->cmd_status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * sigintHandler - signal handler for blocking CTRL-C.
 * @sig_num: signal number.
 *
 * Return: void.
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

/**
 * input_buf - Buffers chained commands.
 * @info: Parameter struct.
 * @buf: Address of buffer.
 * @len: Address of len var.
 *
 * Return: The number of bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
		#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
		#else
		r = _getline(info, buf, &len_p);
		#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->history_count++);
			{
				*len = r;
				info->command_buf = buf;
			}
		}
	}
	return (r);
}
