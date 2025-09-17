#include "exec.h"

int	exec(t_command *cmd, t_mst **env)
{
	int	saved_fd[2];

	saved_fd[0] = dup(STDIN_FILENO);
	saved_fd[1] = dup(STDOUT_FILENO);
	if (get_builtin(cmd->args[0]))
	{
		execute_one_builtin(cmd, env);
		dup2(saved_fd[0], STDOUT_FILENO);
		dup2(saved_fd[1], STDIN_FILENO);
		close(saved_fd[0]);
		close(saved_fd[1]);
		return (0);
	}
	execute_cmd(cmd, env);
	return (0);
}
