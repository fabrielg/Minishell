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

static void	mst_unlink_from_list(t_mst **root, t_mst *to_delete)
{
	t_mst	*current;
	t_mst	*prev;

	if (!root || !*root || !to_delete)
		return ;
	if (*root == to_delete)
	{
		*root = to_delete->next;
		return ;
	}
	current = *root;
	prev = NULL;
	while (current && current != to_delete)
	{
		prev = current;
		current = current->next;
	}
	if (current && prev)
		prev->next = current->next;
}

static t_mst	*mst_find_min(t_mst *node)
{
	if (!node)
		return (NULL);
	while (node->left)
		node = node->left;
	return (node);
}

static t_mst	*mst_delete_from_bst(t_mst **tree, char *key);

static t_mst	*mst_delete_leaf_or_single_child(t_mst **node)
{
    t_mst *to_delete;

	to_delete = *node;
    if (!(*node)->left)
        *node = (*node)->right;
    else
        *node = (*node)->left;
    return (to_delete);
}

static t_mst	*mst_delete_two_children_node(t_mst **node)
{
	t_mst *to_delete;
	t_mst *succ_parent;
	t_mst *succ;
	t_mst *curr;

	to_delete = *node;
	succ_parent = *node;
	succ = (*node)->right;
	curr = succ;
	while (curr->left)
	{
		succ_parent = curr;
		curr = curr->left;
	}
	succ = curr;
	if (succ_parent != *node)
		succ_parent->left = succ->right;
	else
		succ_parent->right = succ->right;
	succ->left = to_delete->left;
	succ->right = to_delete->right;
	*node = succ;
	return (to_delete);
}

static t_mst	*mst_delete_from_bst(t_mst **tree, char *key)
{
	t_mst	*current;
	int		cmp;

	if (!tree || !*tree)
		return (NULL);
	current = *tree;
	cmp = ft_strcmp(current->dic->key, key);
	if (cmp < 0)
		return (mst_delete_from_bst(&current->left, key));
	else if (cmp > 0)
		return (mst_delete_from_bst(&current->right, key));
	else
	{
		if (!current->left || !current->right)
		{
			if (!current->left)
				*tree = current->right;
			else
				*tree = current->left;
			return (current);
		}
		else
			return (mst_delete_two_children_node(tree));
	}
}

int	mst_deletion(t_mst **tree, char *to_delete)
{
    t_mst *node_to_delete;

	node_to_delete = mst_delete_from_bst(tree, to_delete);
	//printf("node to delete:	%p\n", node_to_delete);
	if (!node_to_delete)
		return 1;
	//printf("%s=%s\n", node_to_delete->dic->key, node_to_delete->dic->value);
	//printf("\n\ntree:\n\n");
	//print_tree(*tree);
	mst_unlink_from_list(tree, node_to_delete);
	mst_free(&node_to_delete);
	return 0; // succès
	}
