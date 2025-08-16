/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_nbr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:24:00 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/02/03 16:27:00 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nb_digits_formatted(t_conversion conv, int n)
{
	int	result;

	if (!n && !conv.precision)
		return (0);
	result = ft_nb_digits(n);
	if (conv.precision > result)
		result += (conv.precision - result);
	if (n < 0)
		result++;
	else
	{
		if (conv.flags & SIGNED)
			result++;
		else if (conv.flags & SPACE)
			result++;
	}
	return (result);
}

static char	ft_get_sign_symbol(t_conversion conv, int n)
{
	if (n >= 0 && conv.flags & SIGNED)
		return ('+');
	else if (n >= 0 && conv.flags & SPACE)
		return (' ');
	return ('-');
}

static void	ft_add_int(t_strbuilder *sb, int n, t_conversion conv)
{
	char	*nbr;

	nbr = ft_itoa(n);
	if (nbr)
	{
		if (n == -2147483648)
			ft_sb_append(sb, "2147483648", 10);
		else if (n)
			ft_sb_append(sb, nbr, ft_strlen(nbr));
		else if (n == 0 && conv.precision != 0)
			ft_sb_append(sb, nbr, ft_strlen(nbr));
		free(nbr);
	}
}

void	ft_add_nbr(t_strbuilder *build, t_conversion conv, int n)
{
	char	fill;
	char	sign;
	int		digits;

	digits = ft_nb_digits_formatted(conv, n);
	if (conv.precision != -1)
		fill = ' ';
	else
		fill = ' ' + !!(conv.flags & ZERO_PAD) * ('0' - ' ') * !!digits;
	sign = ft_get_sign_symbol(conv, n);
	if ((conv.flags & SIGNED || conv.flags & SPACE || n < 0) && fill == '0')
		ft_sb_add_char(build, sign);
	if (!(conv.flags & LEFT_ALIGN) && conv.field_width > digits)
		ft_sb_add_nchar(build, fill, conv.field_width - digits);
	if ((conv.flags & SIGNED || conv.flags & SPACE || n < 0) && fill == ' ')
		ft_sb_add_char(build, sign);
	if (conv.precision >= 0 && conv.precision > ft_nb_digits(n))
		ft_sb_add_nchar(build, '0', conv.precision - ft_nb_digits(n));
	if (n < 0)
		n = (unsigned int)-n;
	ft_add_int(build, n, conv);
	if (conv.flags & LEFT_ALIGN && conv.field_width > digits)
		ft_sb_add_nchar(build, fill, conv.field_width - digits);
}
