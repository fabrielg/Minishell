#include "envp.h"

/**
* @brief Displays all key-value pairs in MST list.
* @param mst Root node of MST to display
*/
void	mst_display(t_mst *mst)
{
	t_mst	*tmp;

	tmp = mst;
	while (tmp)
	{
		if (!tmp->dic->value)
			continue;
		printf("%s=%s\n", tmp->dic->key, tmp->dic->value);
		tmp = tmp->next;
	}
}

/**
* @brief Displays all key-value pairs in MST list sorted in ASCII order.
* @param mst Root node of MST to display
*/
void	bst_display(t_mst *tree)
{
	if (!tree)
		return;
	bst_display(tree->right);
	ft_printf("export %s=%s\n", tree->dic->key, tree->dic->value);
	bst_display(tree->left);
}
