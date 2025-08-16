/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:59:20 by gfrancoi          #+#    #+#             */
/*   Updated: 2024/11/25 14:13:08 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*new_calloc;
	unsigned int	calloc_len;

	calloc_len = nmemb * size;
	if (calloc_len < nmemb && calloc_len < size)
		return (NULL);
	new_calloc = malloc(calloc_len);
	if (!new_calloc)
		return (NULL);
	ft_bzero(new_calloc, calloc_len);
	return (new_calloc);
}
