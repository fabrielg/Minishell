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

static t_mst	*mst_unlink_node(t_mst **tree, char *to_unlink)
{
	t_mst	*prev;
	t_mst	*current;
	t_mst	*next;

	// printf("DEBUG: %s\n", to_unlink);
	if (!tree && !(*tree) || !to_unlink)
		return (NULL);
	current = *tree;
	prev = NULL;
	next = current->next;
	while (current)
	{
		// printf("DEBUG 2: %s\n", current->dic->key);
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
		if (next)
			next = next->next;
	}
	// printf("DEBUG 3: %s\n", to_unlink);
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
	if (parent && parent->right == to_delete)
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
	if (parent && is_right)
		parent->right = to_delete;
	else if (parent && !is_right)
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
	if (!parent && parent->right == to_delete)
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
	if (parent && is_right)
		parent->right = to_delete;
	else if (parent && !is_right)
		parent->left = to_delete;
	mst_free(&tmp);
}

static t_mst	*mst_get_successor(t_mst *tree)
{
	tree = tree->right;
	while (tree != NULL && tree->left != NULL)
		tree = tree->left;
	return (tree);
}

static t_mst	*mst_del_node(t_mst *root, char *to_delete)
{
	int		res;
	t_mst	*tmp;
	t_mst	*succ;

	if (!root)
		return (NULL);
	res = ft_strcmp(root->dic->key, to_delete);
	if (res < 0)
		root->left = mst_del_node(root->left, to_delete);
	else if (res > 0)
		root->right = mst_del_node(root->right, to_delete);
	else {
		if (!root->left) {
			tmp = root->right;
			mst_free(&root);
			return (tmp);
		}
		if (!root->right) {
			tmp = root->left;
			mst_free(&root);
			return (tmp);
		}
		succ = mst_get_successor(root);
		root->dic = succ->dic;
		root->right = mst_del_node(root->right, root->dic->key);
	}
	return (root);
}

int	mst_deletion(t_mst **tree, char *to_delete)
{
	t_mst	*node;

	node = mst_unlink_node(tree, to_delete);
	if (!node)
		return (1);
	if (mst_del_node(*tree, to_delete))
		return (0);
	return (1);
}
