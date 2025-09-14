#include "envp.h"

//[DEBUG]_______________________

int debug_node(t_mst *prt, t_mst *child)
{
	printf("\n");
	if (!child)
		return (printf("to_delete not find\n"), 0);
	if (prt)
		printf("parent ->    [%s]\n", prt->dic->key);
	printf("to_delete -> [%s]\n", child->dic->key);
	if (child->left)
	{
		printf("l_child -> [%s]", child->left->dic->key);
		if (child->left->left || child->left->right)
			printf(" (is a parent)\n");
		else
			printf(" (has no childs)\n");
	}
	if (child->right)
	{
		printf("r_child -> [%s]", child->right->dic->key);
		if (child->right->left || child->right->right)
			printf(" (is a parent)\n");
		else
			printf(" (has no childs)\n");
	}
	return (1);
}

//[STATUS]_____________________________________

int get_deletion_status(t_mst *prt, t_mst *child)
{
	if (!child->left && !child->right)
		return (1);
	if (child->left)
		if (child->left->left || child->left->right)
			return (3);
	if (child->right)
		if (child->right->left || child->right->right)
			return (3);
	if (prt)
		return (2);
	return (0);
}

static t_mst *mst_get_min(t_mst *node)
{
	if (!node)
		return NULL;
	if (!node->right)
		return node;
	return (mst_get_min(node->right));
}

//[DELETION]________________________________________

int env_deletion(t_mst **tree, char *key)
{
	bst_display(*tree);
	printf("(%i)\n", mst_size(*tree));
	bool	is_right;
	t_mst	*prt;
	t_mst	*child;
	int		status;

	if (!ft_strcmp(tree[0]->dic->key, key))
		return (printf("ROOT\n"), debug_node(NULL, mst_get_node(*tree, key)));
	mst_unlink(tree, key);
	prt = mst_get_parent(*tree, key);
	child = mst_get_node(*tree, key);
	if (!child)
		return (0);
	status = get_deletion_status(prt, child);
	debug_node(prt, child);
	printf("status : %i\n", status);
	is_right = true;
	if (!prt->right && !ft_strcmp(prt->left->dic->key, key))
		is_right = false;
	if (status == 1)
		no_childs_case(prt, is_right);
	else if (status == 2)
		childs_case(prt, child, is_right);
	else if (status == 3)
		childs_are_parents_case(prt, child, is_right);
	//Case 3
	// mst_free(&child);
	// child = NULL;

	printf("\n\nAFTER________\n\n");
	bst_display(*tree);
	printf("(%i)\n", mst_size(*tree));

	return (1);
}
