/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabrielg <fabrielg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 21:18:55 by fabrielg          #+#    #+#             */
/*   Updated: 2025/08/17 23:12:16 by fabrielg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	mst_add_back(t_mst **root, t_mst *new)
{
	t_mst	*node;
	
	if (root)
	{
		if (!(*root))
			*root = new;
		else
		{
			node = mst_last(*root);
			node->next = new;
		}
	}
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

static void	freekey(t_dic **dic)
{
	if (!dic || !(*dic))
		return ;
	if ((*dic)->key)
		free((*dic)->key);
	free(*dic);
	*dic = NULL;
}

void	mst_clear(t_mst **root)
{
	t_mst	*node;
	t_mst	*next;

	if (!root)
		return ;
	node = *root;
	while (node)
	{
		freekey(&node->dic);
		next = node->next;
		free(node);
		node = next;
	}
}