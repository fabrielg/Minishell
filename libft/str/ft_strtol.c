/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 20:54:39 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/16 21:19:26 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stddef.h>
#include "../libft.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

static int	is_valid_digit(char c, int base)
{
	if (base <= 10)
		return (c >= '0' && c < '0' + base);
	return ((c >= '0' && c <= '9') || (c >= 'a' && c < 'a' + base - 10)
		|| (c >= 'A' && c < 'A' + base - 10));
}

static int	detect_base(const char **str, int base)
{
	if ((base == 0 || base == 16) && **str == '0' && (*(*str + 1) == 'x'
			|| *(*str + 1) == 'X'))
	{
		*str += 2;
		return (16);
	}
	if (base == 0 && **str == '0')
		return (8);
	if (base == 0)
		return (10);
	return (base);
}

static long	handle_overflow(long result, int sign, int base, char c)
{
	long	overflow_check;

	overflow_check = result;
	if (c >= '0' && c <= '9')
		result = result * base + (c - '0');
	if (c >= 'a' && c <= 'z')
		result = result * base + (c - 'a' + 10);
	if (c >= 'A' && c <= 'Z')
		result = result * base + (c - 'A' + 10);
	if (result / base != overflow_check)
	{
		if (sign == 1)
			return (LONG_MAX);
		return (LONG_MIN);
	}
	return (result);
}

long	ft_strtol(const char *str, char **endptr, int base)
{
	long	result;
	int		sign;

	if (base < 2 || base > 36)
		return (0);
	while (is_whitespace(*str))
		str++;
	sign = !(*str == '-') * 2 - 1;
	if (*str == '-' || *str == '+')
		str++;
	base = detect_base(&str, base);
	result = 0;
	while (is_valid_digit(*str, base))
	{
		result = handle_overflow(result, sign, base, *str++);
		if (result == LONG_MAX || result == LONG_MIN)
			break ;
	}
	if (endptr)
		*endptr = (char *)str;
	return (result * sign);
}
