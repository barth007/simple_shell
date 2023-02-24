#include "shell.h"
/**
 *new_node - creates a new node
 *@type: argument
 *Return: struct node_s
**/
struct node_s *new_node(enum node_type_e type)
{
	struct node_s *node;

	node = malloc(sizeof(struct node_s));
	if (!node)
		return (NULL);
	_memset(node, 0, sizeof(struct node_s));
	node->type = type;
	return (node);
}
/**
 *add_child_node - expands the AST of a simple command by
 *adding a new child node
 *@parent: parent node
 *@child: child node
**/
void add_child_node(struct node_s *parent, struct node_s *child)
{
	struct node_s *sibling;

	if (!parent || !child)
		return;
	if (!parent->first_child)
		parent->first_child = child;
	else
	{
		sibling = parent->first_child;
		while (sibling->next_sibling)
			sibling = sibling->next_sibling;
		sibling->next_sibling = child;
		child->prev_sibling = sibling;
	}
	parent->children++;
}
/**
 *set_node_val_str - set a node's value to the given string
 *@node: the node value
 *@val: the given string
**/
void set_node_val_str(struct node_s *node, char *val)
{
	char *val2;

	node->val_type = VAL_STR;
	if (!val)
		node->val.str = NULL;
	else
	{
		val2 = malloc(_strlen(val) + 1);
		if (!val2)
			node->val.str = NULL;
		else
		{
			_strcpy(val2, val);
			node->val.str = val2;
		}
	}
}
/**
 *free_node_tree - frees the memory used by a node structure
 *@node: the node to be freed
**/
void free_node_tree(struct node_s *node)
{
	struct node_s *child;
	struct node_s *next;

	if (!node)
		return;
	child = node->first_child;
	while (child)
	{
		next = child->next_sibling;
		free_node_tree(child);
		child = next;
	}
	if (node->val_type == VAL_STR)
	{
		if (node->val.str)
			free(node->val.str);
	}
	free(node);
}
