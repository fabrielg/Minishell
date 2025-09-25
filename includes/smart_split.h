/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabrielg <fabrielg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 00:31:16 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/08/16 17:03:08 by fabrielg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SMART_SPLIT_H
# define SMART_SPLIT_H

# include <stdbool.h>

typedef struct s_split_ctx
{
	const char	*line;
	char		**tokens;
	int			capacity;
	int			count;
	int			start;
	char		quote;
	bool		can_flush;
}	t_split_ctx;

void	flush_token(t_split_ctx *ctx, int end);
void	flush_operator(t_split_ctx *ctx, int *i);
void	tokens_remove_quotes(t_split_ctx ctx);

#endif