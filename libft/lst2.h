/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:52:08 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/13 18:03:37 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST2_H
# define LST2_H

typedef struct s_list2
{
	void			*content;
	struct s_list2	*next;
	struct s_list2	*prev;
}	t_list2;

t_list2	*ft_lstnew2(void *content);
void	ft_lstadd_front2(t_list2 **lst, t_list2 *new);
size_t	ft_lstsize2(t_list2 *lst);
t_list2	*ft_lstlast2(t_list2 *lst);
void	ft_lstadd_back2(t_list2 **lst, t_list2 *new);
void	ft_lstdelone2(t_list2 *lst, void (*del)(void*));
void	ft_lstclear2(t_list2 **lst, void (*del)(void*));
void	ft_lstiter2(t_list2 *lst, void (*f)(void *));
t_list2	*ft_lstmap2(t_list2 *lst, void *(*f)(void *), void (*del)(void *));
size_t	ft_lstnb_find2(t_list2 *lst, void *to_find);

#endif