#include "shell.h"

/**
 * _isalpha - Check if a character is alphabetic.
 * @c: The character to check.
 *
 * Return: 1 if c is alphabetic, 0 otherwise.
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * string_prefix_equal - checks if needle starts with haystack.
 * @haystack: string to search.
 * @needle: the substring to find.
 *
 * Return: address of next char of haystack or NULL.
 */
char *string_prefix_equal(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 *	string_dupy - creates a duplicate of a string
 *	This function creates a new copy of the input string by allocating
 *				memory for the new string and copying the characters from the
 *				input string to the new string.
 *	The input string should be null-terminated.
 *	@str: the string to duplicate
 *
 *	Return: pointer to the duplicated string, or
 *				NULL if str is NULL or if memory allocation fails.
 */
char *string_dupy(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);

	while (*str++)
		length++;

	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);

	for (length++; length--;)
		ret[length] = *--str;

	return (ret);
}

/**
 * is_chain - tests if current character in buffer is a chain delimiter.
 * @info: parameter struct.
 * @buf: character buffer.
 * @pos: address of current position in buf.
 *		The function checks if a given character in a buffer is a command chain
 *						delimiter in a shell program. It checks for the pipe symbol
 *						followed by another pipe symbol, the ampersand followed by
 *						another ampersand, or a semicolon. If the current character
 *						is a chain delimiter, it modifies the buffer and sets the
 *						command buffer type field in a struct, then returns 1.
 *						Otherwise, it returns 0.
 *
 * Return: 1 if chain delimiter, 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *pos)
{
	size_t j = *pos;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->buf_format = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->buf_format = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->buf_format = CMD_CHAIN;
	}
	else
		return (0);
	*pos = j;
	return (1);
}
