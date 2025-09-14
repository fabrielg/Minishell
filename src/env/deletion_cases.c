#include "envp.h"

void	no_childs_case(t_mst *prt, bool is_right)
{
	if (is_right)
		prt->right = NULL;
	else
		prt->left = NULL;
}

void	childs_case(t_mst *prt, t_mst *child, bool is_right)
{
	if (!child->right) //SI PAS DE CHILD A DROITE
	{
		if (is_right)
			prt->right = child->left;
		else
			prt->left = child->left;
		return ;
	}
	if (child->left)
		child->right->left = child->right;
	if (is_right)
		prt->right = child->right;
	else
		prt->left = child->right;
}

static	t_mst	*mst_get_min(t_mst	*node)
{
	if (!node)
		return NULL;
	if (!node->left)
		return node;
	if (!node->left->left)
		return node;
	return (mst_get_min(node->left));
}

void	childs_are_parents_case(t_mst *prt, t_mst *child, bool is_right)
{
	t_mst	*successor_prt;

	successor_prt = NULL;
	//si il n'y a pas d'enfant à droite allors le to_delete est remplacé par son enfant gauche
	if (!child->right)
	{
		if (is_right)
			prt->right = child->left;
		else
			prt->left = child->left;
		return ;
	}
	successor_prt = mst_get_min(child->right);
	printf("successor prt : %s | successor : %s\n", successor_prt->dic->key, successor_prt->left->dic->key);
	successor_prt->left->left = child->left;
	successor_prt->left->right = successor_prt;
	if (prt && is_right)
		prt->right = successor_prt->left;
	else if (prt)
		prt->left = successor_prt->left;
	debug_node(successor_prt, successor_prt->left);
	successor_prt->left = NULL;
}
