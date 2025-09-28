#include "exec.h"
#include "minishell.h"

/**
 * @brief Executes a command (builtin or external) and updates last exit code.
 * @return 0
 */
int	exec(t_command *cmd, t_minishell *ms)
{
	if (cmd->args[0] != 0 && get_builtin(cmd->args[0], NULL))
	{
		ms->last_exit_code = execute_one_builtin(cmd, ms);
		if (DEBUG_MODE)
			printf("last exit code : %i\n", ms->last_exit_code);
		return (0);
	}
	ms->last_exit_code = execute_cmd(cmd, ms);
	return (0);
}
