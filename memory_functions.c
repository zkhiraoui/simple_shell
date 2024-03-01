/**
 * Introduction
 * These are four utility functions that can be used in C programs:
 *		_memset: This function fills a block of memory with a given byte value.
						It takes three parameters: a pointer to the memory area, the byte
						value to fill it with, and the number of bytes to fill.
						It returns a pointer to the memory area.
 *		free_block: This function frees a pointer and sets its value to NULL.
						It takes a pointer to the address of the pointer to be freed.
						It returns 1 if the pointer was freed, otherwise 0.
 *		deallocate: This function frees memory allocated for an array of strings.
						It takes a pointer to the array of strings.
						It does not return anything.
 *		_realloc: This function reallocates a block of memory to a new size.
						It takes three parameters: a pointer to the previous block
						of memory, the size of the previous block, and the size of
						the new block.
						It returns a pointer to the reallocated block.
*/

#include "shell.h"

/**
 * _memset - fills memory with a constant byte.
 * @s: pointer to the memory area.
 * @b: byte to fill *s with.
 * @n: amount of bytes to fill.
 *
 * Return: a pointer to the memory area s.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;

	return (s);
}

/**
 * free_block - Frees a pointer and NULLs the address.
 * @ptr: Address of the pointer to free.
 *
 * Return: 1 if freed, otherwise 0.
 */
int free_block(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * deallocate - frees a string of strings.
 * @pp: string of strings.
 *
 * This function frees memory allocated for an array of strings.
 * @pp: Pointer to the array of strings.
 */
void deallocate(char **pp)
{
	char **a = pp;

	if (!pp)
		return;

	while (*pp)
		free(*pp++);

	free(a);
}

/**
 * _realloc - reallocates a block of memory.
 * @ptr: pointer to previous malloc'ated block.
 * @old_size: byte size of previous block.
 * @new_size: byte size of new block.
 *
 * Return: pointer to the reallocated block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
