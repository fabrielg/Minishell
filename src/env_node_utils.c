#include "../includes/env.h"
#include <stdio.h>
#include "../libft/libft.h"

t_mst	*mst_last(t_mst *root)
{
	t_mst	*node;

	node = root;
	if (node)
	{
		while (node->next)
			node = node->next;
	}
	return (node);
}


t_dic	*split_env_var(char *env_var)
{
	char	*copy;
	char	*key;
	char	*value;

	copy = ft_strdup(env_var);
	if (!copy)
		return (NULL);
	value = ft_strchr(copy, '=');
	if (!value)
		return (NULL);
	value[0] = 0;
	value++;
	key = copy;
	return (new_dic(key, value));
}

void	mst_add_back(t_mst **root, t_mst *new)
{
	t_mst	*node;
	
	if (!root)
		return ;
	if (!(*root))
		*root = new;
	else
	{
		node = mst_last(*root);
		node->next = new;
	}
}

t_mst	*mst_alloc_env(char **env)
{
	size_t	i;
	t_mst	*root;
	t_dic	*current_var;

	if (!env)
		return (NULL);
	root = NULL;
	i = 0;
	while (env[i])
	{
		current_var = split_env_var(env[i]);
		mst_add_back(&root, new_mst(current_var));
		i++;
	}
	return (root);
}
