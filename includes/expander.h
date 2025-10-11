/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 00:31:16 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/11 02:36:25 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "envp.h"

//[EXPAND]_________________________________________

void	append_segment(char **new_arg, char *arg, int start, int end);
void	expand_checker(char *args[2], int *i, int exit_code, t_mst *env);
void	expand_redirs(t_list2 *redirs, t_mst *env, int exit_code, bool unquote);
void	expand_arg(char **arg_ptr, t_mst *env, int exit_code);
void	expand_command(t_command *cmd, t_mst *env, int exit_code);
int		expand_heredoc(t_redirect *redir, t_mst *env, int exit_code);

#endif
