#include "exec.h"
#include "minishell.h"
#include <wait.h>
#include "sig.h"

/**
 * @brief Frees allocated pipes and PIDs arrays.
 * @return Always returns 1
 */
int	pipe_clear(int (**pipes)[2], pid_t **pids)
{
	if (*pipes)
		free(*pipes);
	if (*pids)
		free(*pids);
	return (1);
}

/**
 * @brief Waits for all forked pipeline processes and sets the last exit code.
 * @return Exit code of the last process
 */
int	wait_forked_pipes(t_minishell *ms, pid_t *pids, int nb_cmds)
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
	g_sig_pid = 0;
	return (ms->last_exit_code);
}

/**
 * @brief Initializes the required number of pipes for a pipeline.
 * @return 0 on success, 1 on failure
 */
int	exec_init_pipes(int (*pipes)[2], int nb_cmd)
{
	int	i;

	i = -1;
	while (++i < nb_cmd - 1)
		if (pipe(pipes[i]) == -1)
			return (1);
	return (0);
}

/**
 * @brief Closes all pipe file descriptors in the pipeline.
 */
void	exec_close_pipes(int (*pipes)[2], int nb_cmds)
{
	int	i;

	i = -1;
	while (++i < nb_cmds - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

/**
 * @brief Forks and executes each command in a pipeline,
 *        setting up pipes between them.
 * @return 0 on success, 1 on fork failure
 */
int	ap_pipes(int (*pipes)[2], pid_t *pids, t_ast *node, t_minishell *ms)
{
	int	i;
	int	nb_cmds;
	int	code;

	i = -1;
	nb_cmds = node->s_pipeline.count;
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
			exec_close_pipes(pipes, nb_cmds);
			code = exec_ast(node->s_pipeline.cmds[i], ms);
			exit(clear_minishell(ms, code));
		}
	}
	return (0);
}
