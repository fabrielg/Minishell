#include "exec.h"

int	exec(t_command *cmd, t_mst **env)
{
	int	i;

	i = -1;
	if (get_builtin(cmd->args[0]))
	{
		execute_one_builtin(cmd, env);
		return (0);
	}
	execute_cmd(cmd, env);
	return (0);
}
