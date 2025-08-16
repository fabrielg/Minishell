/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strbuilder.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:59:41 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/02/26 15:05:30 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRBUILDER_H
# define STRBUILDER_H

# include <stddef.h>

# ifndef SB_SIZE
#  define SB_SIZE 128
# endif

# if SB_SIZE < 2
#  error SB_SIZE must be greater or equal to 2
# endif

typedef struct s_strbuilder	t_strbuilder;
typedef struct s_strbuilder
{
	char			content[SB_SIZE];
	t_strbuilder	*next;
	int				index;
}	t_strbuilder;

t_strbuilder	*ft_sb_new(void);
t_strbuilder	*ft_sb_last(t_strbuilder *sb);
char			*ft_sb_build(t_strbuilder *sb);
void			ft_sb_append(t_strbuilder *sb, char *content, int size);
void			ft_sb_add_char(t_strbuilder *sb, char content);
void			ft_sb_add_nchar(t_strbuilder *sb, char content, size_t nb);
int				ft_sb_display(t_strbuilder *sb);
int				ft_sb_size(t_strbuilder *sb);
int				ft_sb_clear(t_strbuilder **sb);

#endif