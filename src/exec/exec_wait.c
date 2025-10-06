#include "minishell.h"
#include "ast.h"
#include <sys/wait.h>

int	wait_all_commands(t_ast *root)
{	
	t_ast	*node;
	int		status;

	status = 0;
	if (!root)
		return ;
	node = root;
	if (node->type == TOKEN_PIPELINE)
	{
		wait_all_commands(&node->pipeline.left);
		wait_all_commands(&node->pipeline.right);
	}
	else if (node->type == TOKEN_LOGICAL_EXPRESSION)
	{
		wait_all_commands(&node->logical.left);
		wait_all_commands(&node->logical.right);
	}
	else if (node->type == TOKEN_SUBSHELL)
		wait_all_commands(&node->subshell);
	waitpid(root->cmd->pid, &status, 0);
	return (status);
}
