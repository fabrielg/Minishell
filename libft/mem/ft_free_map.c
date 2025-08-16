/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 01:46:25 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/07 11:12:53 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free_map(void **map, int size)
{
	int	i;

	if (!map)
		return (0);
	i = -1;
	while (++i < size)
		free(map[i]);
	free(map);
	return (1);
}
