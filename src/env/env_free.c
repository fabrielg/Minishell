#include "envp.h"

/**
 * @brief Frees dictionary and its key/value, sets pointer to NULL.
 * @param dic Pointer to dictionary pointer
 */
void	freekey(t_dic *dic)
{
	if (!dic)
		return ;
	if (dic->key)
		free(dic->key);
	dic->key = NULL;
}

void	mst_free(t_mst **node)
{
	freekey(&(*node)->dic);
	free(*node);
	*node = NULL;
}

/**
 * @brief Frees entire MST linked list and all dictionaries.
 * @param root Pointer to root pointer (set to NULL after clearing)
 */
void	mst_clear(t_mst **root)
{
	t_mst	*node;
	t_mst	*next;

	if (!root)
		return ;
	node = *root;
	while (node)
	{
		next = node->next;
		mst_free(&node);
		node = next;
	}
}
