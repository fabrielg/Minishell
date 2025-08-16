/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:10:22 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/13 18:02:46 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list2	*ft_lstmap2(t_list2 *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list2	*new_lst;
	t_list2	*new;
	void	*new_content;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		new = ft_lstnew2(new_content);
		if (!new)
		{
			del(new_content);
			ft_lstclear2(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back2(&new_lst, new);
		lst = lst->next;
	}
	return (new_lst);
}
