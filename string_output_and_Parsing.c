#include "shell.h"

/**
 * _putchar - writes the character `c` to stdout
 * @character: The character to print
 *
 * Return: On success, returns 1.
 *				On error, returns -1 and sets errno appropriately.
 */
int _putchar(char character)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (character == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (character != BUF_FLUSH)
		buf[i++] = character;

	return (1);
}

/**
 *_puts - prints an input string.
 *@str: the string to be printed.
 *
 * Return: void.
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * strtow2 - splits a string into words
 * @str: the input string
 * @delim: the delimiter
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char delim)
{
	int i, j, k, m, numwords = 0;
	char **words;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delim && str[i + 1] == delim) ||
		    (str[i] != delim && !str[i + 1]) || str[i + 1] == delim)
			numwords++;

	if (numwords == 0)
		return (NULL);

	words = malloc((1 + numwords) * sizeof(char *));
	if (!words)
		return (NULL);

	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == delim && str[i] != '\0')
			i++;

		k = 0;
		while (str[i + k] != delim && str[i + k] != '\0')
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

		words[j][m] = '\0';
	}

	words[j] = NULL;
	return (words);
}

/**
 * string_strlen - returns the length of a string.
 * @string: the string whose length to check.
 *
 * Return: integer length of string.
 */
int string_strlen(char *string)
{
	int i = 0;

	if (!string)
		return (0);

	while (*string++)
		i++;
	return (i);
}

/**
 * replace_string - Replaces a string with a new string.
 *
 * @old: Pointer to the old string to be replaced.
 * @new: Pointer to the new string to replace the old string.
 *
 * Return: 1 if successful, 0 otherwise.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

