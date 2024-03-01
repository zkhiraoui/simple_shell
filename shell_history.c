/**
 * Introduction: The order is based on the dependencies of the functions, where
 *				get_history_file is called by write_history and read_history.
 *				build_history_list and renumber_history are called by read_history.
 *				Therefore, get_history_file should be called first, followed
 *				by write_history and read_history, and then build_history_list
 *				and renumber_history can be called as needed.
*/

#include "shell.h"

/**
 * get_history_file - returns the full path to the history file.
 * @info: pointer to the info struct.
 *
 * Return: pointer to allocated string containing history
 *				file path or NULL if error.
 */
char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);

	buf = malloc(sizeof(char) * (string_strlen(dir) + string_strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);

	buf[0] = 0;
	string_cpy(buf, dir);
	string_strcat(buf, "/");
	string_strcat(buf, HIST_FILE);

	return (buf);
}

/**
 * write_history - writes a command history to a file.
 * @info: the parameter struct.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		error_putsfd(node->str, fd);
		error_putfd('\n', fd);
	}
	error_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - Reads command history from a file.
 * @info: Pointer to parameter struct.
 *
 * Return: Returns history_count on success, 0 otherwise.
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->history_count = linecount;
	while (info->history_count-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->history_count);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: structure containing potential arguments
 * @buf: buffer containing the command history
 * @linecount: the line number in the history
 *
 * Return: 0 on success
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - Renumber the history linked list after any changes.
 * @info: The struct containing the arguments, used to maintain.
 *
 * Return: The new history count.
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->history_count = i);
}
