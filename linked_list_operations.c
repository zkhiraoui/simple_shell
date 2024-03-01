/**
 * Introduction
 *		add_node - Adds a new node to the start of the linked list.
 *		add_node_end - adds a node to the end of the list.
 *		delete_node_at_index - deletes a node at a specific index.
 *		node_string_prefix_equal - finds the node whose string starts with a given prefix.
 *		get_node_index - gets the index of a node in a linked list.
 */

#include "shell.h"

/**
 * add_node - Adds a new node to the start of the linked list.
 * @head: A pointer to a pointer to the head node.
 * @str: The string to be stored in the node.
 * @num: The node index used by history.
 *
 * Return: The size of the linked list.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);

	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);

	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;

	if (str)
	{
		new_head->str = string_dupy(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}

	new_head->next = *head;
	*head = new_head;

	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list.
 * @head: address of pointer to head node.
 * @str: str field of node.
 * @num: node index used by history.
 *
 * Return: pointer to new node, or NULL on failure.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = string_dupy(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
	{
		*head = new_node;
	}
	return (new_node);
}

/**
 * delete_node_at_index - deletes a node at a specific index.
 * @head: pointer to the head node.
 * @index: index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}

	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * node_string_prefix_equal - finds the node whose string starts with a given prefix.
 * @node: pointer to the head of the list.
 * @prefix: the prefix to match.
 * @c: the next character after prefix to match, or -1 if not needed.
 *
 * Return: pointer to the matching node, or NULL if not found.
 */
list_t *node_string_prefix_equal(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = string_prefix_equal(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node in a linked list.
 * @head: pointer to the head of the linked list.
 * @node: pointer to the node to find the index of.
 *
 * Return: the index of the node or -1 if it's not found.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
