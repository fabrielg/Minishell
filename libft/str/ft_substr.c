/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:50:32 by gfrancoi          #+#    #+#             */
/*   Updated: 2024/11/19 16:37:16 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	sub_len;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (0);
	sub_len = 0;
	s_len = ft_strlen(s);
	while (start < s_len && sub_len < len && s[start + sub_len])
		sub_len++;
	sub = ft_calloc(sub_len + 1, sizeof(char));
	if (!sub)
		return (0);
	i = 0;
	while (i < sub_len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = 0;
	return (sub);
}
