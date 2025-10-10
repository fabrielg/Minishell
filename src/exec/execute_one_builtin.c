#include "exec.h"
#include "minishell.h"

/**
 * @brief Executes a builtin command in the current process.
 * @return Exit code of the builtin
 */
int	execute_one_builtin(t_command *cmd, t_minishell *ms)
{
	t_builtin		f;
	unsigned char	flag;
	unsigned char	exit_code;

	flag = 0b0;
	f = NULL;
	dup2(cmd->pipes[0], STDIN_FILENO);
	dup2(cmd->pipes[1], STDOUT_FILENO);
	if (redirect_cmd(cmd) == ERROR)
		return (REDIR_ERR);
	f = get_builtin(cmd->args[0], &flag);
	if (f)
		exit_code = f(cmd->args, &ms->exports);
	close_pipes(cmd);
	if ((flag & F_EXIT))
		ms->shell_exit_code = handle_exit(cmd, ms, &exit_code);
	dup2(ms->stdin_backup, STDIN_FILENO);
	dup2(ms->stdout_backup, STDOUT_FILENO);
	return (exit_code);
}
