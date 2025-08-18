#include "../includes/env.h"
#include <stdio.h>
#include "../libft/libft.h"

static void	set_quoted(char *value, bool *out)
{
	if (!value)
	{
		*out = false;
		return ;
	}
	// TODO: make a strchr using a char set instead of a simple char
	if (!value[0] || ft_strchr(value, ' ') || ft_strchr(value, '='))
		*out = true;
	else
		*out = false;
}

t_dic	*new_dic(char *key, char *value)
{
	t_dic	*dic;

	dic = (t_dic *) malloc(sizeof(t_dic));
	if (!dic)
		return (NULL);
	dic->key = key;
	dic->value = value;
	set_quoted(dic->value, &dic->quoted);
	return (dic);
}

t_mst	*new_mst(t_dic *dic)
{
	t_mst	*new;

	new = (t_mst *) ft_calloc(1, sizeof(t_mst));
	if (!new)
		return (NULL);
	new->dic = dic;
	return (new);
}
