/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:28:56 by gfrancoi          #+#    #+#             */
/*   Updated: 2024/11/19 12:00:28 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	if (n <= 0)
		return (dest);
	if (!dest && !src)
		return (0);
	while (n--)
		*((char *)dest + n) = *((char *)src + n);
	return (dest);
}
