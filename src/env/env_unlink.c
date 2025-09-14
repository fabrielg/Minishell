#include "envp.h"

int mst_unlink(t_mst **tree, char *key)
{
	t_mst *curr;
	t_mst *prev;

	if (!tree|| !*tree)
		return 0;
	curr = *tree;
	prev = NULL;
	while (curr && ft_strcmp(curr->dic->key, key) != 0)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return 0;
	if (!prev)
		*tree = curr->next;
	else
		prev->next = curr->next;
	curr->next = NULL;
	return 1;
}
