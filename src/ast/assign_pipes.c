#include "ast.h"

int	assign_pipes(t_ast *node)
{
	int	fd[2];

	if (!node)
		return (0);
	if (node->type == TOKEN_PIPELINE)
	{
		if (pipe(fd) == -1)
			return (perror("pipe"), 1);
		if (node->pipeline.left && node->pipeline.left->type == TOKEN_COMMAND)
			node->pipeline.left->cmd->pipes[1] = fd[1];
		if (node->pipeline.right && node->pipeline.right->type == TOKEN_COMMAND)
			node->pipeline.right->cmd->pipes[0] = fd[0];
		assign_pipes(node->pipeline.left);
		assign_pipes(node->pipeline.right);
	}
	else if (node->type == TOKEN_LOGICAL_EXPRESSION)
	{
		assign_pipes(node->logical.left);
		assign_pipes(node->logical.right);
	}
	else if (node->type == TOKEN_SUBSHELL)
		assign_pipes(node->subshell);
	return (0);
}
