/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnb_find2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:30:38 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/13 18:03:03 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lstnb_find2(t_list2 *lst, void *to_find)
{
	size_t	count;
	t_list2	*node;

	count = 0;
	node = lst;
	while (node)
	{
		if (node->content == to_find)
			count++;
		node = node->next;
	}
	return (count);
}
