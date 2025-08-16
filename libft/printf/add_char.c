/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:13:59 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/02/03 16:26:54 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_add_char(t_strbuilder *build, t_conversion conv, int c)
{
	static int	nb_display = 1;

	if (conv.specifier == 'c')
	{
		if (conv.flags & LEFT_ALIGN)
			ft_sb_add_char(build, c);
		if (nb_display < (conv.field_width) && conv.field_width > 0)
			ft_sb_add_nchar(build, ' ', (conv.field_width) - nb_display);
		if (!(conv.flags & LEFT_ALIGN))
			ft_sb_add_char(build, c);
	}
	else
		ft_sb_add_char(build, conv.specifier);
}
