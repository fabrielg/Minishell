#include "envp.h"

static t_mst	*mst_search(t_mst *tree, char *to_find, t_mst *parent, bool get_parent)
{
	int	res;

	if (!tree || !to_find)
		return (NULL);
	res = ft_strcmp(tree->dic->key, to_find);
	if (res == 0 && get_parent)
		return (parent);
	else if (res == 0)
		return (tree);
	if (res < 0)
		return (mst_search(tree->right, to_find, tree, get_parent));
	return (mst_search(tree->left, to_find, tree, get_parent));
}

t_mst	*mst_get_parent(t_mst *tree, char *child)
{
	return (mst_search(tree, child, NULL, true));
}

t_mst	*mst_get_node(t_mst *tree, char *to_find)
{
	return (mst_search(tree, to_find, NULL, false));
}
