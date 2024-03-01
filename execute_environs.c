#include "shell.h"

/**
 * _getenv - get the value of an environment variable.
 * @info: structure containing the environment variables.
 * @name: name of the environment variable to get the value of.
 *
 * Return: the value of the environment variable, NULL if not found.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = string_prefix_equal(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _setenv - Set or modify an environment variable.
 * @info: Structure containing arguments. Used to maintain function prototype.
 * @var: Name of the environment variable to set or modify.
 * @value: Value to set for the environment variable.
 *
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(string_strlen(var) + string_strlen(value) + 2);
	if (!buf)
		return (1);
	string_cpy(buf, var);
	string_strcat(buf, "=");
	string_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = string_prefix_equal(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->environ_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->environ_changed = 1;

	return (0);
}

/**
 * _unsetenv - Remove an environment variable.
 * @info: structure containing potential arguments and environment variables.
 * @var: the name of the environment variable to be removed.
 *
 * Return: 1 on successful removal, 0 otherwise.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = string_prefix_equal(node->str, var);
		if (p && *p == '=')
		{
			info->environ_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}

	return (info->environ_changed);
}
