#include "exec.h"
#include "minishell.h"

int	execute_one_builtin(t_command *cmd, t_minishell *ms)
{
	t_builtin		f;
	unsigned char	flag;
	unsigned char	exit_code;

	flag = 0b0;
	f = NULL;
	if (redirect_cmd(cmd) == ERROR)
		return (REDIR_ERROR);
	f = get_builtin(cmd->args[0], &flag);
	if (f)
		exit_code = f(cmd->args, &ms->exports);
	if (flag & F_EXIT)
		ms->shell_exit_code = (int)exit_code;
	dup2(ms->stdin_backup, STDIN_FILENO);
	dup2(ms->stdout_backup, STDOUT_FILENO);
	return (exit_code);
}
