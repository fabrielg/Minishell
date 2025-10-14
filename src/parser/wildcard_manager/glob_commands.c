/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:21:51 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:21:52 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tokens.h"
#include "wildcard.h"

/**
 * @brief Expands glob patterns in all commands of a token list.
 */
void	glob_commands(t_list2 *tokens)
{
	t_list2		*curr;
	t_token		*tok;
	t_command	*cmd;

	curr = tokens;
	while (curr)
	{
		tok = (t_token *) curr->content;
		if (tok->type == TOKEN_COMMAND)
		{
			cmd = (t_command *)tok->data;
			glob_one_command(cmd);
			glob_redirects_list(cmd->redirects);
		}
		curr = curr->next;
	}
}
