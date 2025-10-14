/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_min.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:09:09 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:09:09 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"

/**
 * @brief Finds the min node or its parent in a BST subtree.
 * @param tree    Root of the subtree
 * @param get_prt If true, returns parent of min node
 * @return Pointer to min node or parent, NULL if not found
 */
static t_mst	*mst_search_min_generic(t_mst *tree, bool get_prt)
{
	t_mst	*cur;

	if (!tree || !tree->right)
		return (NULL);
	cur = tree->right;
	if (!get_prt)
	{
		while (cur->left)
			cur = cur->left;
		return (cur);
	}
	if (!cur->left)
		return (NULL);
	while (cur->left->left)
		cur = cur->left;
	return (cur);
}

/**
 * @brief Finds the parent of the node with the smallest key in linked list.
 * @return Pointer to parent node, or NULL if first node is minimal
 */
t_mst	*mst_get_linked_min_parent(t_mst *tree)
{
	t_mst	*cur;
	char	*min_key;

	if (!tree || !tree->next)
		return (NULL);
	cur = tree;
	min_key = mst_get_min(tree)->dic.key;
	if (!ft_strcmp(cur->dic.key, min_key))
		return (NULL);
	while (cur->next && ft_strcmp(cur->next->dic.key, min_key))
		cur = cur->next;
	return (cur);
}

/**
 * @brief Finds the node with the smallest key in BST subtree.
 * @return Pointer to minimal node, or NULL if empty
 */
t_mst	*mst_get_min(t_mst *tree)
{
	return (mst_search_min_generic(tree, false));
}

/**
 * @brief Finds the parent of the node with smallest key in BST subtree.
 * @return Pointer to parent of minimal node, or NULL if minimal node is root
 */
t_mst	*mst_get_min_parent(t_mst *tree)
{
	return (mst_search_min_generic(tree, true));
}
