#include "envp.h"

/**
 * @brief Frees dictionary and its key/value, sets pointer to NULL.
 * @param dic Pointer to dictionary pointer
 */
static void	freekey(t_dic **dic)
{
	if (!dic || !(*dic))
		return ;
	if ((*dic)->key)
		free((*dic)->key);
	free(*dic);
	*dic = NULL;
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
		freekey(&node->dic);
		next = node->next;
		free(node);
		node = next;
	}
}
