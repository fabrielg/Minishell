/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:11:51 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:13:45 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "sig.h"
#include <wait.h>

/**
 * @brief Executes a pipeline AST node, handling pipe creation,
 *        forking, and cleanup.
 * @return Exit status of the last command in the pipeline
 */
int	exec_pipeline(t_ast *node, t_minishell *ms)
{
	int		nb_cmds;
	int		status;

	signal(SIGINT, &handle_sigint_pipeline);
	nb_cmds = node->s_pipeline.count;
	ms->child_pids = ft_calloc(nb_cmds, sizeof(pid_t));
	ms->pipes = ft_calloc(nb_cmds - 1, sizeof(int [2]));
	if (!ms->child_pids || (nb_cmds > 1 && !ms->pipes))
		return (pipe_clear(ms->pipes, ms->child_pids));
	if (exec_init_pipes(ms->pipes, nb_cmds)
		|| ap_pipes(ms->pipes, ms->child_pids, node, ms))
		return (pipe_clear(ms->pipes, ms->child_pids));
	exec_close_pipes(ms->pipes, nb_cmds);
	status = wait_forked_pipes(ms, ms->child_pids, nb_cmds);
	signal(SIGINT, &handle_sigint);
	pipe_clear(ms->pipes, ms->child_pids);
	return (status);
}
