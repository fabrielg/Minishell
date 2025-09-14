#include "envp.h"

int	debug_node(t_mst *node)
{
	printf("\n");
	if (!node)
		return (printf("node not found\n"), 0);
	printf("node -> [%s]\n", node->dic->key);
	if (node->left)
	{
		printf("l_child -> [%s]", node->left->dic->key);
		if (node->left->left || node->left->right)
			printf(" (is a parent)\n");
		else
			printf(" (has no childs)\n");
	}
	if (node->right)
	{
		printf("r_child -> [%s]", node->right->dic->key);
		if (node->right->left || node->right->right)
			printf(" (is a parent)\n");
		else
			printf(" (has no childs)\n");
	}
	if (node->next)
		return (printf("next > [%s]\n\n", node->next->dic->key), 0);
	return (printf("next > NULL\n\n"), 1);
}
