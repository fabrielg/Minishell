/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:55:08 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/02/03 16:59:18 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	gnl_strjoin(char **s1, char *s2)
{
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;
	char	*join;

	s1_len = ft_strlen_char(*s1, 0);
	s2_len = ft_strlen_char(s2, 0);
	join = ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (!join)
		return ((void) 0);
	i = 0;
	while (*s1 && (*s1)[i])
	{
		join[i] = (*s1)[i];
		i++;
	}
	while (s2[i - s1_len])
	{
		join[i] = s2[i - s1_len];
		i++;
	}
	join[i] = 0;
	free(*s1);
	*s1 = join;
}

void	gnl_strcut(char **to_cut, char **paste)
{
	char	*temp;
	int		len;
	int		new_line_index;

	if (!(*to_cut))
		return ;
	len = ft_strlen(*to_cut);
	new_line_index = ft_has_char(*to_cut, '\n');
	if (new_line_index == -1)
		new_line_index = len;
	*paste = ft_substr(*to_cut, 0, new_line_index + 1);
	if (new_line_index == len)
		temp = NULL;
	else
		temp = ft_substr(*to_cut, new_line_index + 1, len - new_line_index + 1);
	free(*to_cut);
	*to_cut = temp;
}
