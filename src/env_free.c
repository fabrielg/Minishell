#include "../includes/env.h"
#include <stdio.h>
#include "../libft/libft.h"

static void	freekey(t_dic **dic)
{
	if (!dic || !(*dic))
		return ;
	if ((*dic)->key)
		free((*dic)->key);
	free(*dic);
	*dic = NULL;
}

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
