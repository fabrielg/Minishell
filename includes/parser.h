/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabrielg <fabrielg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 23:23:16 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/09/08 23:23:16 by fabrielg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "minishell.h"

/* Functions utils for parsing */
t_list2	*parser(char *command_line, t_mst *env, int exit_code);
void	expander(t_list2 *tokens, t_mst *env, int exit_code);
t_list2	*group_commands(t_list2 *tokens);
t_list2	*tokenize(char **contents);
void	flush_command(t_list2 **result, t_command **current);

#endif