#include "exec.h"
#include "minishell.h"
#include <wait.h>

static int	wait_forked_pipes(t_minishell *ms, pid_t *pids, int nb_cmds)
{
	int	i;
	int	status;

	i = -1;
	while (++i < nb_cmds)
		waitpid(pids[i], &status, 0);
	if (WIFEXITED(status))
		ms->last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ms->last_exit_code = 128 + WTERMSIG(status);
	return (ms->last_exit_code);
}

static int	init_pipes(int (*pipes)[2], int nb_cmd)
{
	int	i;

	i = -1;
	while (++i < nb_cmd)
	{
		if (pipe(pipes[i]) == -1)
			return (1);
	}
	return (0);
}

static void	close_all_pipes(int (*pipes)[2], int nb_cmds)
{
	int	i;

	i = -1;
	while (++i < nb_cmds - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

static int	app_pipes(int (*pipes)[2], pid_t *pids, t_ast *node , t_minishell *ms)
{
	int	i;
	int	nb_cmds;
	int	code;

	i = -1;
	nb_cmds = node->pipeline.count;
	while (++i < nb_cmds)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (1);
		if (pids[i] == 0)
		{
			if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (i < nb_cmds - 1)
				dup2(pipes[i][1], STDOUT_FILENO);
			close_all_pipes(pipes, nb_cmds);
			code = exec_ast(node->pipeline.cmds[i], ms);
			exit(clear_minishell(ms, code));
		}
	}
	return (0);
}

int	exec_pipeline(t_ast *node, t_minishell *ms)
{
	int		nb_cmds = node->pipeline.count;
	pid_t	pids[nb_cmds];
	int		pipes[nb_cmds - 1][2];

	if (init_pipes(pipes, nb_cmds) == 1)
		return (1);
	if (app_pipes(pipes, pids, node, ms) == 1)
		return (1);
	close_all_pipes(pipes, nb_cmds);
	return (wait_forked_pipes(ms, pids, nb_cmds));
}
