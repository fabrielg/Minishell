/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:34:36 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/02/03 16:27:16 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_sprintf(t_strbuilder *build, const char *s, va_list args)
{
	char			*next_conv;
	t_conversion	conv;

	next_conv = ft_strchr(s, '%');
	while (next_conv)
	{
		ft_sb_append(build, (char *)s, (int)(next_conv - s));
		add_formatted(build, next_conv, args, &conv);
		s += (int)(next_conv - s) + conv.length;
		next_conv = ft_strchr(s, '%');
	}
	ft_sb_append(build, (char *)s, ft_strlen(s));
}

void	add_formatted(t_strbuilder *b, char *s, va_list args, t_conversion *c)
{
	ft_memset(c, 0, sizeof(t_conversion));
	if (ft_parse(s, c))
		apply_specifier(b, *c, args);
	else
		ft_sb_append(b, s, c->length);
}

void	apply_specifier(t_strbuilder *build, t_conversion conv, va_list args)
{
	if (conv.specifier == 'c')
		ft_add_char(build, conv, va_arg(args, int));
	else if (conv.specifier == 's')
		ft_add_str(build, conv, va_arg(args, char *));
	else if (conv.specifier == 'd' || conv.specifier == 'i')
		ft_add_nbr(build, conv, va_arg(args, int));
	else if (conv.specifier == 'u')
		ft_add_unsigned(build, conv, va_arg(args, unsigned int), 0);
	else if (conv.specifier == 'x')
		ft_add_unsigned(build, conv, va_arg(args, unsigned int), 1);
	else if (conv.specifier == 'X')
		ft_add_unsigned(build, conv, va_arg(args, unsigned int), 2);
	else if (conv.specifier == 'p')
		ft_add_pointer(build, conv, va_arg(args, unsigned long));
	else if (conv.specifier == '%')
		ft_add_char(build, conv, '%');
}

int	ft_printf(const char *s, ...)
{
	t_strbuilder	*build;
	va_list			args;
	int				nb_display;

	if (!s)
		return (-1);
	build = ft_sb_new();
	va_start(args, s);
	ft_sprintf(build, s, args);
	va_end(args);
	nb_display = ft_sb_size(build);
	ft_sb_display(build);
	ft_sb_clear(&build);
	return (nb_display);
}
