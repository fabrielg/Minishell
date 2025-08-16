/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:50:15 by gfrancoi          #+#    #+#             */
/*   Updated: 2024/11/19 11:50:15 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_digit(long int n)
{
	int	result;

	if (n < 0)
		n *= -1;
	result = 1;
	while (n > 9)
	{
		n /= 10;
		result++;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char		*result;
	long int	nbr;
	int			digits;

	nbr = n;
	digits = nb_digit(nbr);
	if (n < 0)
	{
		nbr *= -1;
		digits++;
	}
	result = ft_calloc((digits + 1), sizeof(char));
	if (!result)
		return (NULL);
	result[digits] = 0;
	while (digits--)
	{
		result[digits] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}
