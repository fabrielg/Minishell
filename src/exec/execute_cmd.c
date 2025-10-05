#include "exec.h"
#include "minishell.h"
#include "sig.h"
#include <sys/wait.h>

/**
 * @brief Executes a command in the child process.
 * @return Exit code of executed command or error code
 */
static t_uint8	child_exec(t_command *cmd, t_minishell *ms)
{
	t_mst			*env_path;
	t_uint8			exit_code;

	exit_code = -1;
	if (redirect_cmd(cmd) == ERROR)
		return (REDIR_ERR);
	if (!*(cmd->args[0]))
		return (exec_err(cmd->args[0], NOT_FOUND_MSG, NOT_FOUND_ERR));
	if (is_builtin(cmd->args, &ms->exports, &exit_code))
		return (exit_code);
	if (is_abs_rltv_path(cmd->args, ms->exports, &exit_code))
		return (exit_code);
	env_path = mst_get_node(ms->exports, "PATH");
	if (!env_path)
		return (exec_err(cmd->args[0], NO_PATH_MSG, NOT_FOUND_ERR));
	if (is_in_path(cmd->args, env_path, ms->exports, &exit_code))
		return (exit_code);
	return (exec_err(cmd->args[0], NOT_FOUND_MSG, NOT_FOUND_ERR));
}

/**
 * @brief Forks and executes a command in a child process.
 * @return Exit status of command, or error code
 */
int	execute_cmd(t_command *cmd, t_minishell *ms)
{
	pid_t			pid;
	int				status;
	t_uint8			exit_code;

	exit_code = 1;
	if (!cmd)
		return (NOT_FOUND_ERR);
	pid = fork();
	if (pid == -1)
		return (ERROR);
	if (pid == 0)
	{
		reset_signals();
		exit_code = child_exec(cmd, ms);
		printf("exit code : %i\n", exit_code);
		exit(clear_minishell(ms, exit_code));
	}
	g_sig_pid = pid;
	waitpid(pid, &status, 0);
	g_sig_pid = 0;
	return (cmd_exit_status(status));
}
