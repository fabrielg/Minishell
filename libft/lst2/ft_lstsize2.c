/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:30:38 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/13 17:57:35 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lstsize2(t_list2 *lst)
{
	size_t	count;
	t_list2	*node;

	count = 0;
	node = lst;
	while (node)
	{
		node = node->next;
		count++;
	}
	return (count);
}
