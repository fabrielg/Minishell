/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:09:32 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/02/03 16:27:05 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_min(int a, int b)
{
	if (a <= b)
		return (a);
	return (b);
}

static char	*ft_get_str_null(t_conversion conv)
{
	if (conv.precision >= 6 || conv.precision < 0)
		return ("(null)");
	return ("");
}

void	ft_add_str(t_strbuilder *build, t_conversion conv, char *s)
{
	int	precision;
	int	len;

	if (!s)
		s = ft_get_str_null(conv);
	len = ft_strlen((const char *)s);
	precision = ft_get_min(len, conv.precision);
	if (precision < 0)
		precision = len;
	if (conv.flags & LEFT_ALIGN && s)
		ft_sb_append(build, s, precision);
	if (conv.field_width > precision)
		ft_sb_add_nchar(build, ' ', conv.field_width - precision);
	if (!(conv.flags & LEFT_ALIGN) && s)
		ft_sb_append(build, s, precision);
}
