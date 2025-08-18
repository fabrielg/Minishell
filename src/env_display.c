#include "../includes/env.h"
#include <stdio.h>
#include "../libft/libft.h"

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
