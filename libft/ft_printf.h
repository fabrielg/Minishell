/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:34:45 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/02/07 18:01:25 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "strbuilder.h"
# include "macro.h"

# define PREFIX		0b00001 // #
# define ZERO_PAD	0b00010 // 0
# define LEFT_ALIGN	0b00100 // -
# define SPACE		0b01000 // ' '
# define SIGNED		0b10000 // +

typedef struct s_specifier
{
	char	c;
	int		(*f)(va_list arg);
}	t_specifier;

typedef struct s_conversion
{
	char		specifier;
	char		flags;
	int			field_width;
	int			precision;
	int			length;
}	t_conversion;

typedef struct s_base
{
	char			*digits;
	unsigned int	size;
	char			*prefix;
}	t_base;

int		ft_printf(const char *s, ...);
int		ft_parse(const char *format, t_conversion *conv);
void	add_formatted(t_strbuilder *b, char *s, va_list args, t_conversion *c);
void	apply_specifier(t_strbuilder *build, t_conversion conv, va_list args);

void	ft_add_char(t_strbuilder *build, t_conversion conv, int c);

void	ft_add_str(t_strbuilder *build, t_conversion conv, char *s);

void	ft_add_nbr(t_strbuilder *build, t_conversion conv, int n);

void	ft_add_unsigned(t_strbuilder *build, t_conversion conv, t_ul n, t_ui i);

void	ft_add_pointer(t_strbuilder *build, t_conversion conv, t_ul address);

#endif
