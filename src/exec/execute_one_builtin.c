#include "exec.h"

int	execute_one_builtin(t_command *cmd, t_mst **env)
{
	t_builtin	f;

	f = NULL;
	if (redirect_cmd(cmd) == ERROR)
		return (REDIR_ERROR);
	f = get_builtin(cmd->args[0]);
	if (f)
		f(cmd->args, env);
	return (SUCCESS);
}
