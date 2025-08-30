#include "envp.h"

void	print_tree(t_mst *tree)
{
	if (!tree)
		return;
	print_tree(tree->right);
	ft_printf("%s=%s\n", tree->dic->key, tree->dic->value);
	print_tree(tree->left);
}

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
		return (mst_search(tree->left, to_find, tree, get_parent));
	return (mst_search(tree->right, to_find, tree, get_parent));
}

t_mst	*mst_get_parent(t_mst *tree, char *child)
{
	return (mst_search(tree, child, NULL, true));
}

t_mst	*mst_get_node(t_mst *tree, char *to_find)
{
	return (mst_search(tree, to_find, NULL, false));
}

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
		bst_insertion(&(*tmp)->left, node);
	else
		bst_insertion(&(*tmp)->right, node);
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
