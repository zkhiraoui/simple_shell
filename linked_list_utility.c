/**
 * Introduction
 *		list_len: Returns the number of nodes in a linked list.
 *		list_to_strings: creates an array of strings from a linked list.
 *		free_list: frees all nodes of a linked list.
 */

#include "shell.h"

/**
 * list_len - Returns the number of nodes in a linked list.
 * @h: Pointer to the first node in the list.
 *
 * Return: The number of nodes in the list.
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - creates an array of strings from a linked list.
 * @head: pointer to the first node of the list.
 *
 * Return: array of strings, or NULL if an error occurs.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);

	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(string_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = string_cpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * free_list - frees all nodes of a linked list.
 * @head_ptr: pointer to pointer to head node.
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
