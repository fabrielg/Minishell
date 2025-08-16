/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbuilder_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:54:11 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/02/26 15:06:10 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_sb_build(t_strbuilder *sb)
{
	char	*build;
	int		index;
	int		size;

	size = ft_sb_size(sb);
	if (size < 1)
		return (0);
	build = ft_calloc(size, sizeof(char) + 1);
	if (!build)
		return (NULL);
	index = 0;
	while (sb)
	{
		ft_memcpy((build + index), sb->content, sb->index + 1);
		index += sb->index;
		sb = sb->next;
	}
	return (build);
}

int	ft_sb_display(t_strbuilder *sb)
{
	char	*build;
	int		nb_display;

	build = ft_sb_build(sb);
	if (!build)
		return (-1);
	nb_display = ft_putstr_fd(build, 1);
	free(build);
	return (nb_display);
}

int	ft_sb_size(t_strbuilder *sb)
{
	int	size;

	size = 0;
	if (sb)
	{
		size += (SB_SIZE - 1);
		while (sb->next)
		{
			size += (SB_SIZE - 1);
			sb = sb->next;
		}
		size -= ((SB_SIZE - 1) - sb->index);
	}
	return (size);
}

int	ft_sb_clear(t_strbuilder **sb)
{
	if (!*sb || !sb)
		return (0);
	ft_sb_clear(&(*sb)->next);
	free(*sb);
	*sb = NULL;
	return (1);
}
