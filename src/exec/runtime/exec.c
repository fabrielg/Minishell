#include "minishell.h"
#include "exec.h"

int	exec_ast(t_ast *node, t_minishell *ms)
{
	if (!node)
		return (0);
	if (node->type == TOKEN_COMMAND)
		return (exec_command(node->cmd, ms));
	else if (node->type == TOKEN_PIPELINE)
		return (exec_pipeline(node, ms));
	else if (node->type == TOKEN_LOGICAL_EXPRESSION)
		return (exec_logical(node, ms));
	else if (node->type == TOKEN_SUBSHELL)
		return (exec_subshell(node, ms));
	return (1);
}
