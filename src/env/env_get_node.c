#include "envp.h"

/**
 * @brief Searches for a node or its parent in BST by key.
 * @param tree     Root of BST
 * @param key      Key to search
 * @param parent   Current parent node (used internally)
 * @param get_prt  If true, return parent of matching node
 * @return Pointer to node or parent, NULL if not found
 */
static t_mst	*mst_search(t_mst *tree, char *key, t_mst *parent, bool get_prt)
{
	int	res;

	if (!tree || !key)
		return (NULL);
	res = ft_strcmp(tree->dic.key, key);
	if (res == 0 && get_prt)
		return (parent);
	else if (res == 0)
		return (tree);
	if (res < 0)
		return (mst_search(tree->right, key, tree, get_prt));
	return (mst_search(tree->left, key, tree, get_prt));
}

/**
 * @brief Finds the parent of a node with given key "child" in BST.
 * @return Pointer to parent node, or NULL if root or not found
 */
t_mst	*mst_get_parent(t_mst *tree, char *child)
{
	return (mst_search(tree, child, NULL, true));
}

/**
 * @brief Finds the node with given key "to_find" in BST.
 * @return Pointer to node, or NULL if root or not found
 */
t_mst	*mst_get_node(t_mst *tree, char *to_find)
{
	return (mst_search(tree, to_find, NULL, false));
}
