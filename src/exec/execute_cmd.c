#include "exec.h"
#include <errno.h>
#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

int	child_exec(t_command *cmd, t_minishell *ms)
{
	t_mst			*env_path;
	int				exit_code;

	exit_code = -1;
	if (redirect_cmd(cmd) == ERROR)
		return (REDIR_ERR);
	if (is_builtin(cmd->args, &ms->exports, &exit_code))
		return (exit_code);
	if (is_abs_rltv_path(cmd->args, ms->exports, &exit_code))
		return (exit_code);
	env_path = mst_get_node(ms->exports, "PATH");
	if (!env_path)
		return (exec_error(cmd->args[0], NO_PATH_MSG, NOT_FOUND_ERR));
	if (is_in_path(cmd->args, env_path, ms->exports, &exit_code))
		return (exit_code);
	return (exec_error(cmd->args[0], NOT_FOUND_MSG, NOT_FOUND_ERR));
}

int	execute_cmd(t_command *cmd, t_minishell *ms)
{
	pid_t			pid;
	int				status;
	unsigned char	exit_code;

	exit_code = 1;
	if (!cmd)
		return (NOT_FOUND_ERR);
	pid = fork();
	if (pid == -1)
		return (ERROR);
	if (pid == 0)
	{
		exit_code = child_exec(cmd, ms);
		exit(clear_minishell(ms, exit_code));
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
	}
	return (SUCCESS);
}
