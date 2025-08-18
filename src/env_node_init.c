#include "../includes/env.h"
#include <stdio.h>
#include "../libft/libft.h"

static void	set_quoted(char *value, unsigned char *out)
{
	const char	*char_quoted = " !\"#$&()*-;<>=?[]\\^`{}|~";

	if (!value)
	{
		*out = 0;
		return ;
	}
	if (ft_strchr(value, '\''))
		*out = 2;
	else if (!value[0] || ft_strchrset(value, char_quoted))
		*out = 1;
	else
		*out = 0;
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
