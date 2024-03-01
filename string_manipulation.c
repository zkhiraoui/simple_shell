#include "shell.h"

/**
 * _atoi - Convert a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The converted number, or 0 if no numbers in string.
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

/**
 * exit_strchr - Find the first occurrence of a character in a string.
 * @s: The string to be searched.
 * @c: The character to be found.
 *
 * Return: A pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found.
 */
char *exit_strchr(char *s, char c)
{
	do {
		if (*s == c)
		{
			return (s);
		}
	} while (*s++ != '\0');

	return (NULL);
}

/**
 * exit_strncpy - Copy a string to a specified length.
 * @dest: The destination string to be copied to.
 * @src: The source string to be copied from.
 * @n: The amount of characters to be copied.
 *
 * Return: The destination string.
 */
char *exit_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}

	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}

	return (s);
}

/**
 * string_strcat - concatenates two strings
 * @dest: pointer to the destination buffer
 * @src: pointer to the source buffer
 *
 * Return: pointer to the destination buffer
 */
char *string_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
	{
		dest++;
	}
	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = *src;

	return (ret);
}

/**
 * string_cpy - Copies a string.
 * @dest: Pointer to the destination buffer.
 * @src: Pointer to the source buffer.
 *
 * Return: Pointer to destination buffer.
 */
char *string_cpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
	{
		return (dest);
	}
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;

	return (dest);
}
