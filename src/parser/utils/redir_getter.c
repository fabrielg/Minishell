/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_getter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:21:47 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:21:47 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

/**
 * @brief Retrieves the list of redirections from a command token.
 * @return Pointer to redirection list, or NULL if none
 */
t_list2	*get_redir_lst(t_token *token)
{
	t_command	*cmd;

	if (token->type != TOKEN_COMMAND)
		return (NULL);
	cmd = (t_command *)token->data;
	if (cmd && cmd->redirects)
		return (cmd->redirects);
	return (NULL);
}
