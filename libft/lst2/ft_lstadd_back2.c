/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:42:03 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/13 18:00:08 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back2(t_list2 **lst, t_list2 *new)
{
	t_list2	*node;

	if (lst)
	{
		if (!(*lst))
			*lst = new;
		else
		{
			node = ft_lstlast2(*(lst));
			node->next = new;
			new->prev = node;
		}
	}
}
