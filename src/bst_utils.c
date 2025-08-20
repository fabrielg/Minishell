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

static t_mst	*mst_search(t_mst *tree, char *to_find, t_mst *parent, bool get_parent)
{
	int	res;

	if (!tree)
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

static t_mst	**mst_unlink_node(t_mst **tree, char *to_unlink)
{
	t_mst	*prev;
	t_mst	*current;
	t_mst	*next;

	if (!tree && !(*tree))
		return (NULL);
	current = *tree;
	prev = NULL;
	next = current->next;
	while (current)
	{
		if (ft_strcmp(current->dic->key, to_unlink) == 0)
		{
			if (prev == NULL)
				*tree = next;
			else
				prev->next = next;
			return (current);
		}
		prev = current;
		current = current->next;
		next = next->next;
	}
	return (NULL);
}

static int	mst_childcount(t_mst *node)
{
	int	count;

	if (!node)
		return (0);
	count = 0;
	if (node->left)
		count++;
	if (node->right)
		count++;
	return (count);
}

static void	mst_deletion_one_child(t_mst *to_delete, t_mst *parent)
{
	t_mst	*tmp;
	t_mst	*left;
	t_mst	*right;
	bool	is_right;

	is_right = false;
	if (parent->right == to_delete)
		is_right = true;
	tmp = to_delete;
	left = to_delete->left;
	right = to_delete->right;
	if (right)
	{	
		to_delete = right;
		left = to_delete->left;
	}
	else if (left)
		to_delete = left;
	if (is_right)
		parent->right = to_delete;
	else
		parent->left = to_delete;
	mst_free(&tmp);
}

static void	mst_deletion_n_child(t_mst *to_delete, t_mst *parent)
{
	t_mst	*tmp;
	t_mst	*successor;
	bool	is_right;

	tmp = to_delete;
	successor = to_delete->right;
	is_right = false;
	if (parent->right == to_delete)
		is_right = true;
	if (!to_delete->right)
	{
		to_delete = to_delete->left;
		mst_free(&tmp);
		return ;
	}
	while (successor->left)
		successor = successor->left;
	to_delete = successor;
	successor->right = tmp->right;
	successor->left = tmp->left;
	if (is_right)
		parent->right = to_delete;
	else
		parent->left = to_delete;
	mst_free(&tmp);
}

int	mst_deletion(t_mst **tree, char *to_delete)
{
	t_mst	*node;
	t_mst	*parent;

	node = mst_unlink_node(tree, to_delete);
	parent = mst_get_parent(*tree, node->dic->key);
	if (!node)
		return (1);
	if (!node->left && !node->right)
		mst_free(&node);
	else if (!mst_childcount(node->left) 
		&& !mst_childcount(node->right))
		mst_deletion_one_child(node, parent);
	else
		mst_deletion_n_child(node, parent);
}