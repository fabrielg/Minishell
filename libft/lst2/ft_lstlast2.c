/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:38:24 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/13 17:58:27 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list2	*ft_lstlast2(t_list2 *lst)
{
	t_list2	*node;

	node = lst;
	if (node)
	{
		while (node->next)
			node = node->next;
	}
	return (node);
}
