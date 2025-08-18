#include "envp.h"

void	print_tree(t_mst *tree, int depth)
{
	if (!tree)
		return;
	print_tree(tree->right, depth + 1);
	for (int i = 0; i < depth; i++)
		printf("    ");
	ft_printf("%s=%s\n", tree->dic->key, tree->dic->value);
	print_tree(tree->left, depth + 1);
}

t_mst	*mst_search(t_mst *tree, char *to_find)
{
	int	res;

	if (!tree)
		return (NULL);
	res = ft_strcmp(tree->dic->key, to_find);
	if (res == 0)
		return (tree);
	if (res < 0)
		return (mst_search(tree->left, to_find));
	return (mst_search(tree->right, to_find));
}

int	mst_insertion(t_mst **tree, t_mst *node)
{
	int	res;

	if (!(*tree))
	{
		*tree = node;
		return (1);
	}
	res = ft_strcmp((*tree)->dic->key, node->dic->key);
	if (res == 0)
		return (0);
	else if (res < 0)
		mst_insertion(&(*tree)->left, node);
	else
		mst_insertion(&(*tree)->right, node);
	return (0);
}