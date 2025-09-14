#include "envp.h"

static t_mst *mst_search_min_generic(t_mst *tree, bool get_parent)
{
	t_mst	*cur;

	if (!tree || !tree->right)
		return (NULL);
	cur = tree->right;
	if (!get_parent)
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

t_mst	*mst_get_linked_min_parent(t_mst *tree)
{
	t_mst	*cur;
	char	*min_key;

	if (!tree || !tree->next)
		return NULL;
	cur = tree;
	min_key = mst_get_min(tree)->dic.key;
	if (!ft_strcmp(cur->dic.key, min_key))
		return NULL;
	while (cur->next && ft_strcmp(cur->next->dic.key, min_key))
		cur = cur->next;
	return (cur);
}

t_mst	*mst_get_min(t_mst *tree)
{
	return (mst_search_min_generic(tree, false));
}

t_mst	*mst_get_min_parent(t_mst *tree)
{
	return (mst_search_min_generic(tree, true));
}






