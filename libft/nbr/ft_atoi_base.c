/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:29:39 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/03/07 19:07:06 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	all_unique_char(char *str)
{
	int	i;
	int	j;
	int	length;

	i = 0;
	length = ft_strlen(str);
	while (i < length)
	{
		j = i + 1;
		while (j < length)
		{
			if (str[i] == str[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	is_base_string_correct(char *base, int size)
{
	int	i;

	if (size <= 1)
		return (0);
	i = 0;
	while (i < size)
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		if ((base[i] >= 9 && base[i] <= 13) || base[i] == ' ')
			return (0);
		i++;
	}
	return (all_unique_char(base));
}

/*
return the first index where char to_find is in str, else return -1
*/
static int	get_index(char *str, char to_find, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (str[i] == to_find)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	size_t	i;
	int		result;
	int		base_size;
	int		sign;

	base_size = ft_strlen(base);
	if (!is_base_string_correct(base, base_size))
		return (0);
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	while ((str[i] == '-' || str[i] == '+') && i < ft_strlen(str))
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	result = 0;
	while (i < ft_strlen(str))
	{
		if (get_index(base, str[i], base_size) == -1)
			break ;
		result = result * base_size + (get_index(base, str[i++], base_size));
	}
	return (result * sign);
}
