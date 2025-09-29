#include "ast.h"

static t_command	*find_rightmost_cmd(t_ast *node)
{
	if (!node)
		return NULL;
	if (node->type == TOKEN_COMMAND)
		return node->cmd;
	else if (node->type == TOKEN_PIPELINE)
		return find_rightmost_cmd(node->pipeline.right);
	else if (node->type == TOKEN_LOGICAL_EXPRESSION)
		return find_rightmost_cmd(node->logical.right);
	else if (node->type == TOKEN_SUBSHELL)
		return find_rightmost_cmd(node->subshell);
	return NULL;
}

int	assign_pipes(t_ast *node)
{
	int			fd[2];
	t_command	*left_most;

	if (!node)
		return (0);
	if (node->type == TOKEN_PIPELINE)
	{
		if (pipe(fd) == -1)
			return (perror("pipe"), 1);
		left_most = find_rightmost_cmd(node->pipeline.left);
        if (left_most)
            left_most->pipes[1] = fd[1];
		if (node->pipeline.right && node->pipeline.right->type == TOKEN_COMMAND)
			node->pipeline.right->cmd->pipes[0] = fd[0];
		else
			assign_pipes(node->pipeline.right);
		assign_pipes(node->pipeline.left);
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
