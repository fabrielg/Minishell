#include "exec.h"
#include "minishell.h"
#include "wildcard.h"
#include "expander.h"
#include "sig.h"
#include "parser.h"

/**
 * @brief Expands, globs, and executes a single command.
 *        Runs builtins directly or external commands via fork/exec.
 * @return Last exit code of the executed command
 */
int	exec_command(t_command *cmd, t_minishell *ms)
{
	expand_command(cmd, ms->exports, ms->last_exit_code);
	glob_one_command(cmd);
	glob_redirects_list(cmd->redirects);
	expand_heredocs(cmd->redirects, ms);
	if (cmd->args[0] != 0 && get_builtin(cmd->args[0], NULL))
	{
		ms->last_exit_code = run_one_builtin(cmd, ms);
		return (ms->last_exit_code);
	}
	run_cmd(cmd, ms);
	return (ms->last_exit_code);
}
