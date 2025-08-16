/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:05:38 by gfrancoi          #+#    #+#             */
/*   Updated: 2024/11/19 12:10:23 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t count)
{
	while (count-- > 0)
		((unsigned char *)dest)[count] = c;
	return (dest);
}

void	*ft_super_memset(void *dest, void *src, size_t count, size_t srcsize)
{
	size_t	i;

	i = 0;
	while (i < (count * srcsize))
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i % srcsize];
		i++;
	}
	return (dest);
}
