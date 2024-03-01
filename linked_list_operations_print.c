/**
 * Introduction
 *		print_list - prints all elements of a list_t linked list.
 *		print_list_str - prints the string element of a linked list.
 */

#include "shell.h"

/**
 * print_list - prints all elements of a list_t linked list.
 * @h: pointer to first node.
 *
 * Return: size of list.
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * print_list_str - prints the string element of a linked list.
 * @h: pointer to first node.
 * Return: size of the linked list.
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}
