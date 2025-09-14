#include "envp.h"

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
	res = ft_strcmp((*tmp)->dic->key, node->dic->key);
	if (res == 0)
		return (1);
	else if (res < 0)
		bst_insertion(&(*tmp)->right, node);
	else
		bst_insertion(&(*tmp)->left, node);
	return (0);
}

static void	mst_update_value(t_mst *node, t_dic *new_dic)
{
	if (!node || !new_dic)
		return ;
	if (node->dic)
		freekey(&node->dic);
	node->dic = new_dic;
}

int	mst_insertion(t_mst **root, t_mst *node)
{
	t_mst	*existing;

	if (!node || !node->dic)
		return (1);
	existing = mst_get_node(*root, node->dic->key);
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
