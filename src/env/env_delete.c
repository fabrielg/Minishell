/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:09:01 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:09:01 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"

static int		mst_unlink(t_mst **tree, char *key);
static t_mst	*replace_node(t_mst *node);

/**
 * @brief Deletes a node with given key from MST.
 * @return 1 if deleted, 0 otherwise
 */
int	mst_delete(t_mst **tree, char *key)
{
	t_mst	*prt;
	t_mst	*node;
	t_mst	**prt_child;

	prt = mst_get_parent(*tree, key);
	node = mst_get_node(*tree, key);
	if (!node || !mst_unlink(tree, key))
		return (0);
	prt_child = tree;
	if (prt && prt->left == node)
		prt_child = &prt->left;
	else if (prt)
		prt_child = &prt->right;
	*prt_child = replace_node(node);
	mst_free(&node);
	return (1);
}

/**
 * @brief Unlinks a node from the linked list of MST nodes.
 * @return 1 if unlinked, 0 on failure
 */
static int	mst_unlink(t_mst **tree, char *key)
{
	t_mst	*curr;
	t_mst	*prev;

	if (!tree || !*tree)
		return (0);
	if (!(*tree)->next)
		return (1);
	curr = *tree;
	prev = NULL;
	while (curr && ft_strcmp(curr->dic.key, key))
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return (0);
	if (!prev)
	{
		mst_get_linked_min_parent(*tree)->next = mst_get_min(*tree)->next;
		mst_get_min(*tree)->next = (*tree)->next;
		return (1);
	}
	prev->next = curr->next;
	curr->next = NULL;
	return (1);
}

/**
 * @brief Replaces a deleted MST node with proper successor.
 * @return Pointer to new subtree root after replacement
 */
static t_mst	*replace_node(t_mst *node)
{
	t_mst	*parent;
	t_mst	*successor;

	if (!node->left && !node->right)
		return (NULL);
	if (!node->right)
		return (node->left);
	if (!node->left)
		return (node->right);
	parent = mst_get_min_parent(node);
	if (!parent)
	{
		successor = node->right;
		successor->left = node->left;
		return (successor);
	}
	successor = parent->left;
	parent->left = successor->right;
	successor->left = node->left;
	successor->right = node->right;
	return (successor);
}
