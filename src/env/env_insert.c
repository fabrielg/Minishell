#include "envp.h"

/**
 * @brief Inserts a node into BST according to key order.
 * @param tree Pointer to BST root
 * @param node Node to insert
 * @return 0 on success, 1 on failure or duplicate
 */
static int	bst_insertion(t_mst **tree, t_mst *node)
{
	int		res;
	t_mst	**tmp;

	if (!node)
		return (1);
	tmp = tree;
	if (!(*tmp))
	{
		*tmp = node;
		return (0);
	}
	res = ft_strcmp((*tmp)->dic.key, node->dic.key);
	if (res == 0)
		return (1);
	else if (res < 0)
		bst_insertion(&(*tmp)->right, node);
	else
		bst_insertion(&(*tmp)->left, node);
	return (0);
}

/**
 * @brief Updates the dictionary value of an existing MST node.
 */
static void	mst_update_value(t_mst *node, t_dic new_dic)
{
	if (!node || !new_dic.key)
		return ;
	if (node->dic.key)
		freekey(&node->dic);
	node->dic = new_dic;
}

/**
 * @brief Inserts node into MST (linked + BST) or updates value if key exists.
 * @return 0 on success, 1 on failure
 */
int	mst_insertion(t_mst **root, t_mst *node)
{
	t_mst	*existing;

	if (!node || !node->dic.key)
		return (1);
	existing = mst_get_node(*root, node->dic.key);
	if (existing)
	{
		mst_update_value(existing, node->dic);
		free(node);
	}
	else
	{
		mst_add_back(root, node);
		bst_insertion(root, node);
	}
	return (0);
}
