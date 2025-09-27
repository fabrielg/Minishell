/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 23:23:16 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/09/27 18:17:14 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "minishell.h"

# define HEREDOC_PATH "/tmp/minishell_heredoc_"

//[PARSING]________________________________

t_list2	*parser(t_minishell *ms);
t_list2	*tokenize(char **contents);
t_list2	*group_commands(t_list2 *tokens);
int		handle_heredocs(t_list2 *tokens, t_minishell *ms);
void	expander(t_list2 *tokens, t_mst *env, int exit_code);
void	glob_commands(t_list2 *tokens);

//[GETTER]____________________________

t_list2	*get_redir_lst(t_token *token);

//[GROUP_COMMANDS_UTILS]________________________________

void	flush_command(t_list2 **result, t_command **current);

//[HANDLE_HEREDOCS_UTILS]________________________________

int		create_heredoc(t_redirect *rdr, t_minishell *ms);
char	*get_heredoc_name(int heredoc_id);
int		heredoc_exit_status(int status, t_redirect *rdr, t_minishell *ms);
void	heredoc_read_loop(int fd, char *limiter);

#endif
