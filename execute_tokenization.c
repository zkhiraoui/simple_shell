/**
 * Introduction
 *		strtow: Splits a string into an array of words, using a delimiter string
 *			to determine word boundaries.
 *		string_strcmp: Performs a lexicographic comparison of two strings, returning
 *			negative if the first string is less than the second, positive if the
 *			first string is greater than the second, and zero if they are equal.
 *		is_delim: Checks if a character is a delimiter, given a delimiter string.
 *		replace_alias: Replaces an alias in the command line argument array,
 *			if it matches a predefined alias.
 *		replace_vars: Replaces environment variables in the command line
 *			argument array, if they match a predefined format.
 */

#include "shell.h"

/**
 * is_delim - Check if a character is a delimiter.
 * @c: The character to check.
 * @delim: The delimiter string.
 *
 * Return: 1 if true, 0 if false.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
			return (1);
	}
	return (0);
}

/**
 * strtow - splits a string into words, ignoring repeat delimiters.
 * @str: the input string.
 * @delims: the delimiter string.
 *
 * Return: a pointer to an array of strings, or NULL on failure.
 */
char **strtow(char *str, char *delims)
{
	int i, j, k, m, numwords = 0;
	char **words;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	if (!delims)
		delims = " ";

	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], delims) && (is_delim(str[i + 1], delims) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);

	words = malloc((1 + numwords) * sizeof(char *));
	if (!words)
		return (NULL);

	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], delims))
			i++;

		k = 0;
		while (!is_delim(str[i + k], delims) && str[i + k])
			k++;

		words[j] = malloc((k + 1) * sizeof(char));
		if (!words[j])
		{
			for (k = 0; k < j; k++)
				free(words[k]);
			free(words);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			words[j][m] = str[i++];
		words[j][m] = 0;
	}

	words[j] = NULL;
	return (words);
}

/**
 * string_strcmp - performs lexicographic comparison of two strings.
 * @string1: the first string.
 * @string2: the second string.
 *
 * Return: negative if string1 < string2, positive if string1 > string2,
 *			and zero if string1 == string2.
 */
int string_strcmp(char *string1, char *string2)
{
	while (*string1 && *string2)
	{
		if (*string1 != *string2)
			return (*string1 - *string2);

		string1++;
		string2++;
	}

	if (*string1 == *string2)
		return (0);
	else
		return (*string1 < *string2 ? -1 : 1);
}

/**
 * replace_alias - Replaces an alias in the tokenized string.
 *
 * @info: Pointer to the parameter struct.
 *
 * Return: 1 if successful, 0 otherwise.
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_string_prefix_equal(info->alias, info->argv[0], '=');
		if (!node)
			return (0);

		free(info->argv[0]);

		p = exit_strchr(node->str, '=');
		if (!p)
			return (0);

		p = string_dupy(p + 1);
		if (!p)
			return (0);

		info->argv[0] = p;
	}

	return (1);
}

/**
 * replace_vars - Replaces variables in the tokenized string.
 *
 * @info: Pointer to the parameter struct.
 *
 * Return: 1 if successful, 0 otherwise.
 */
int replace_vars(info_t *info)
{
	int i;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!string_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				string_dupy(convert_number(info->cmd_status, 10, 0)));
			continue;
		}

		if (!string_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				string_dupy(convert_number(getpid(), 10, 0)));
			continue;
		}

		node = node_string_prefix_equal(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				string_dupy(exit_strchr(node->str, '=') + 1));
			continue;
		}

		replace_string(&info->argv[i], string_dupy(""));
	}

	return (0);
}
