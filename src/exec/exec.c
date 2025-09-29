#include "exec.h"
#include "minishell.h"
#include "ast.h"

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

static int	exec_pipeline(t_ast *node, t_minishell *ms)
{
	int left_status;
	int right_status;

	if (!node || node->type != TOKEN_PIPELINE)
		return (1);
	left_status = exec_ast(node->pipeline.left, ms);
	(void) left_status;
	right_status = exec_ast(node->pipeline.right, ms);
	if (node->pipeline.left && node->pipeline.left->type == TOKEN_COMMAND)
	{
		if (node->pipeline.left->cmd->pipes[1] != -1)
			close(node->pipeline.left->cmd->pipes[1]);
	}
	if (node->pipeline.right && node->pipeline.right->type == TOKEN_COMMAND)
	{
		if (node->pipeline.right->cmd->pipes[0] != -1)
			close(node->pipeline.right->cmd->pipes[0]);
	}
	return (right_status);
}

int	exec_ast(t_ast *node, t_minishell *ms)
{
	if (!node)
		return (0);
	if (node->type == TOKEN_COMMAND)
		return (exec(node->cmd, ms));
	else if (node->type == TOKEN_PIPELINE)
		return (exec_pipeline(node, ms));
	/*else if (node->type == TOKEN_LOGICAL_EXPRESSION)
		return (exec_logical(node, ms));
	else if (node->type == TOKEN_SUBSHELL)
		return (exec_subshell(node, ms));*/
	return (1);
}
