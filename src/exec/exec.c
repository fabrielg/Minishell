#include "exec.h"
#include "minishell.h"
#include "ast.h"
#include "expander.h"
#include "wildcard.h"
#include <wait.h>

/**
 * @brief Executes a command (builtin or external) and updates last exit code.
 * @return last exit code
 */
int	exec(t_command *cmd, t_minishell *ms)
{
	expand_command(cmd, ms->exports, ms->last_exit_code);
	glob_one_command(cmd);
	glob_redirects_list(cmd->redirects);
	if (cmd->args[0] != 0 && get_builtin(cmd->args[0], NULL))
	{
		ms->last_exit_code = execute_one_builtin(cmd, ms);
		if (DEBUG_MODE)
			printf("last exit code : %i\n", ms->last_exit_code);
		return (ms->last_exit_code);
	}
	execute_cmd(cmd, ms, true);
	return (ms->last_exit_code);
}

static int	exec_logical(t_ast *node, t_minishell *ms)
{
	int	left_status;
	int	right_status;

	left_status = exec_ast(node->logical.left, ms);
	right_status = 0;
	if (node->logical.op == LOGICAL_AND)
	{
		if (left_status == 0)
			right_status = exec_ast(node->logical.right, ms);
		else
			right_status = left_status;
	}
	else if (node->logical.op == LOGICAL_OR)
	{
		if (left_status != 0)
			right_status = exec_ast(node->logical.right, ms);
		else
			right_status = left_status;
	}
	ms->last_exit_code = right_status;
	return (right_status);
}

static int	exec_subshell(t_ast *node, t_minishell *ms)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	pid = fork();
	if (pid == -1)
		return (ERROR);
	else if (pid == 0)
	{
		exit_code = exec_ast(node->subshell, ms);
		exit(clear_minishell(ms, exit_code));
	}
	else
	{
		waitpid(pid, &status, 0);
		ms->last_exit_code = cmd_exit_status(status);
		return (ms->last_exit_code);
	}
}

int	exec_ast(t_ast *node, t_minishell *ms)
{
	if (!node)
		return (0);
	if (node->type == TOKEN_COMMAND)
		return (exec(node->cmd, ms));
	else if (node->type == TOKEN_PIPELINE)
		return (exec_pipeline(node, ms));
	else if (node->type == TOKEN_LOGICAL_EXPRESSION)
		return (exec_logical(node, ms));
	else if (node->type == TOKEN_SUBSHELL)
		return (exec_subshell(node, ms));
	return (1);
}
