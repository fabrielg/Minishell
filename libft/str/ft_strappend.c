/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:21:38 by gfrancoi          #+#    #+#             */
/*   Updated: 2024/11/19 12:34:25 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strappend(char **s, char *to_append)
{
	size_t	append_len;
	size_t	s_len;
	char	*new_s;

	if (!s || !to_append || !*to_append)
		return ;
	s_len = 0;
	if (*s)
		s_len = ft_strlen(*s);
	append_len = ft_strlen(to_append);
	new_s = malloc((s_len + append_len + 1) * sizeof(char));
	if (!new_s)
		return ;
	if (*s)
		ft_memcpy(new_s, *s, s_len);
	ft_memcpy(new_s + s_len, to_append, append_len);
	new_s[s_len + append_len] = 0;
	free(*s);
	*s = new_s;
}

void	ft_strnappend(char **s, char *to_append, size_t size)
{
	size_t	append_len;
	size_t	s_len;
	char	*new_s;

	if (!s || !to_append || !*to_append)
		return ;
	s_len = 0;
	if (*s)
		s_len = ft_strlen(*s);
	append_len = ft_strlen(to_append);
	if (size < append_len)
		append_len = size;
	new_s = malloc((s_len + append_len + 1) * sizeof(char));
	if (!new_s)
		return ;
	if (*s)
		ft_memcpy(new_s, *s, s_len);
	ft_memcpy(new_s + s_len, to_append, append_len);
	new_s[s_len + append_len] = 0;
	free(*s);
	*s = new_s;
}
