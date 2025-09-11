#include "minishell.h"

char	**list2_to_tab(t_list2 *lst)
{
	int		i;
	char	**tab;
	t_list2	*curr;

	if (!lst)
		return (NULL);
	i = 0;
	curr = lst;
	tab = ft_calloc(ft_lstsize2(curr) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	while (curr)
	{
		tab[i] = get_word(curr->content)->text;
		printf("tab[%i] : [%s]\n", i, tab[i]);
		i++;
		curr = curr->next;
	}
	tab[i] = NULL;
	return (tab);
}
