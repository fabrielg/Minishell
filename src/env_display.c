#include "../includes/env.h"

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
		ft_printf("%s=%s\n", tmp->dic->key, tmp->dic->value);
		tmp = tmp->next;
	}
}
