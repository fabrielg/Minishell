/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:34:51 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/02/07 17:56:58 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "limits.h"

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		sign;
	int		result;
	size_t	length;

	i = 0;
	sign = 1;
	length = ft_strlen(nptr);
	while (i < length && ft_strchr(" \t\n\r\v\f", nptr[i]))
		i++;
	if (i < length && (nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (i < length)
	{
		if (!ft_isdigit(nptr[i]))
			return (sign * result);
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * result);
}

int	ft_atoi_strict(const char *nptr, int *dest)
{
	int		sign;
	long	nbr;

	*dest = 0;
	nbr = 0;
	sign = 1;
	if (*nptr == '-' && nptr++)
		sign = -1;
	if (!*nptr)
		return (0);
	while (*nptr)
	{
		if (!ft_isdigit(*nptr))
			return (0);
		nbr = nbr * 10 + (*nptr - '0');
		nptr++;
	}
	nbr *= sign;
	if (nbr < INT_MIN || nbr > INT_MAX)
		return (0);
	*dest = nbr;
	return (1);
}
