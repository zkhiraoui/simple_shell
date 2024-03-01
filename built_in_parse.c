#include "shell.h"

/**
 * unset_alias - removes an alias from the linked list of aliases
 * @info: pointer to struct containing command information
 * @str: the alias to be removed
 *
 * Return: Always return 1 on failure to remove, 0 on success
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = exit_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_string_prefix_equal(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * _myalias - Mimics the alias built_in command
 * @info: Pointer to the parameter struct. Used to maintain
 *
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = exit_strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_string_prefix_equal(info->alias, info->argv[i], '='));
	}

	return (0);
}

/**
 * set_alias - Sets an alias for a string command
 * @info: Pointer to the parameter struct
 * @str: The alias string
 *
 * Return: 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = exit_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * copy_chars - Duplicates characters.
 * @pathstr: The PATH string.
 * @start: Starting index.
 * @stop: Stopping index.
 *
 * Return: Pointer to new buffer.
 */
char *copy_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}
