#include "exec.h"
#include "minishell.h"
#include <wait.h>

int	exec_pipeline(t_ast *node, t_minishell *ms)
{
	int		nb_cmds;
	pid_t	*pids;
	int		(*pipes)[2];
	int		status;

	nb_cmds = node->s_pipeline.count;
	pids = ft_calloc(nb_cmds, sizeof(pid_t));
	pipes = ft_calloc(nb_cmds - 1, sizeof(int [2]));
	if (!pids || (nb_cmds > 1 && !pipes))
		return (pipe_clear(&pipes, &pids));
	if (exec_init_pipes(pipes, nb_cmds) || ap_pipes(pipes, pids, node, ms))
		return (pipe_clear(&pipes, &pids));
	exec_close_pipes(pipes, nb_cmds);
	status = wait_forked_pipes(ms, pids, nb_cmds);
	pipe_clear(&pipes, &pids);
	return (status);
}
