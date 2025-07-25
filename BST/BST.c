/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 19:34:10 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/07/25 21:08:25 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BST.h"
#include <stdlib.h>
#include <stdio.h>

static void	print_tree(t_tree *tree, int depth)
{
	if (!tree)
		return;

	print_tree(tree->right_child, depth + 1);

	for (int i = 0; i < depth; i++)
		printf("    ");
	printf("%d\n", tree->value);

	print_tree(tree->left_child, depth + 1);
}

void	bs_display(t_tree *tree)
{
	print_tree(tree, 0);
}

t_tree	*bs_new(int value, t_tree *left, t_tree *right)
{
	t_tree	*new;

	new = malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new->value = value;
	new->left_child = left;
	new->right_child = right;
	return (new);
}

t_tree	*bs_search(t_tree *tree, int to_find)
{
	if (!tree)
		return (NULL);
	if (tree->value == to_find)
		return (tree);
	if (tree->value > to_find)
		return (bs_search(tree->left_child, to_find));
	return (bs_search(tree->right_child, to_find));
}

int	bs_insertion(t_tree **tree, int value)
{
	if (!(*tree))
	{
		*tree = bs_new(value, NULL, NULL);
		return (1);
	}
	else if ((*tree)->value == value)
		return (0);
	else if ((*tree)->value > value)
		bs_insertion(&(*tree)->left_child, value);
	else
		bs_insertion(&(*tree)->right_child, value);
	return (0);
}

void	bs_clear(t_tree *tree)
{
	if (!tree)
		return ;
	bs_clear(tree->left_child);
	bs_clear(tree->right_child);
	free(tree);
}
