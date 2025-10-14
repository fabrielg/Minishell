/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_newtab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:09:18 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:09:18 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"

/**
 * @brief Counts the number of nodes in a linked MST.
 * @return Number of nodes
 */
int	mst_size(t_mst *tree)
{
	int		size;
	t_mst	*curr;

	size = 0;
	curr = tree;
	while (curr)
	{
		curr = curr->next;
		size++;
	}
	return (size);
}

/**
 * @brief Creates a new environment array from MST nodes.
 * @return NULL-terminated array of "KEY=VALUE" strings,
 * or NULL on allocation failure
 */
char	**env_newtab(t_mst *tree)
{
	int		i;
	char	**tab;
	t_mst	*curr;

	curr = tree;
	i = 0;
	tab = calloc(mst_size(tree) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	while (curr)
	{
		if (curr->dic.value[0])
			curr->dic.value[-1] = '=';
		tab[i] = curr->dic.key;
		curr = curr->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
