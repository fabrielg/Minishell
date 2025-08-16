/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:00:57 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/13 18:02:00 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear2(t_list2 **lst, void (*del)(void*))
{
	t_list2	*node;

	while (*lst)
	{
		node = (*lst)->next;
		ft_lstdelone2(*lst, del);
		*lst = node;
	}
	*lst = NULL;
}
