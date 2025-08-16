/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 02:09:33 by gfrancoi          #+#    #+#             */
/*   Updated: 2024/11/19 12:32:17 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	if ((!big || !little) && !len)
		return (0);
	little_len = ft_strlen(little);
	if (!little_len)
		return ((char *)big);
	i = 0;
	while (big[i] && (len - i >= little_len))
	{
		j = 0;
		while (little[j])
		{
			if (big[i + j] != little[j])
				break ;
			j++;
		}
		if (j == little_len)
			return ((char *)big + i);
		i++;
	}
	return (0);
}
