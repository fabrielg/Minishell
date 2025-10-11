#include "exec.h"
#include "minishell.h"

static int	set_right_status(t_ast *node, t_minishell *ms, int left_status)
{
	if (node->s_logical.op == LOGICAL_AND && left_status == 0)
		return (exec_ast(node->s_logical.right, ms));
	if (node->s_logical.op == LOGICAL_OR && left_status != 0)
		return (exec_ast(node->s_logical.right, ms));
	if (node->s_logical.op == LOGICAL_AND || node->s_logical.op == LOGICAL_OR)
		return (left_status);
	return (0);
}

int	exec_logical(t_ast *node, t_minishell *ms)
{
	int	left_status;
	int	right_status;

	left_status = exec_ast(node->s_logical.left, ms);
	right_status = set_right_status(node, ms, left_status);
	ms->last_exit_code = right_status;
	return (right_status);
}
