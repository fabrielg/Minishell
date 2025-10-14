/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:11:56 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:11:57 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/**
 * @brief Executes an AST node based on its type and updates the last exit
 *        code in the minishell structure.
 * @return Exit status of the executed node
 */
int	exec_ast(t_ast *node, t_minishell *ms)
{
	if (!node)
		return (0);
	if (ms->signal_received)
	{
		ms->signal_received = false;
		return (ms->last_exit_code);
	}
	if (node->type == TOKEN_COMMAND)
		return (exec_command(node->cmd, ms));
	else if (node->type == TOKEN_PIPELINE)
		return (exec_pipeline(node, ms));
	else if (node->type == TOKEN_LOGICAL_EXPRESSION)
		return (exec_logical(node, ms));
	else if (node->type == TOKEN_SUBSHELL)
		return (exec_subshell(node, ms));
	return (1);
}
