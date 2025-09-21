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
		if (tmp->dic.value)
			ft_printf("%s=%s\n", tmp->dic.key, tmp->dic.value);
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
		return ;
	bst_display(tree->left);
	write(STDOUT_FILENO, "export ", 7);
	write(STDOUT_FILENO, tree->dic.key, ft_strlen(tree->dic.key));
	write(STDOUT_FILENO, "='", 2);
	if (tree->dic.value)
		write(STDOUT_FILENO, tree->dic.value, ft_strlen(tree->dic.value));
	write(STDOUT_FILENO, "'\n", 2);
	bst_display(tree->right);
}
