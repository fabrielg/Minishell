/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabrielg <fabrielg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 01:08:18 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/08/18 16:20:36 by fabrielg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchrset(const char *s, char *set)
{
	int		i;
	char	*res;

	if (!set || !s)
		return (NULL);
	i = 0;
	while (set[i])
	{
		res = ft_strchr(s, set[i]);
		if (res)
			return (res);
		i++;
	}
	return (NULL);
}
