#include "exec.h"
#include "minishell.h"
#include <wait.h>

/**
 * @brief Executes a subshell AST node in a child process and updates
 *        the last exit code.
 * @return Exit status of the subshell
 */
int	exec_subshell(t_ast *node, t_minishell *ms)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	pid = fork();
	if (pid == -1)
		return (ERROR);
	if (pid == 0)
	{
		exit_code = exec_ast(node->subshell, ms);
		exit(clear_minishell(ms, exit_code));
	}
	waitpid(pid, &status, 0);
	ms->last_exit_code = cmd_exit_status(status);
	return (ms->last_exit_code);
}
