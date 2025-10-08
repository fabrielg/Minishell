#include "ast.h"

t_ast	*ast_new_command(t_command *cmd)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = TOKEN_COMMAND;
	node->cmd = cmd;
	return (node);
}

t_ast	*ast_new_pipeline(t_ast **cmds, size_t count)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);

	node->type = TOKEN_PIPELINE;
	node->pipeline.count = count;
	node->pipeline.cmds = cmds;

	return (node);
}

t_ast	*ast_new_logical(t_logical_op op, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = TOKEN_LOGICAL_EXPRESSION;
	node->logical.op = op;
	node->logical.left = left;
	node->logical.right = right;
	return (node);
}

t_ast	*ast_new_subshell(t_ast *sub)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = TOKEN_SUBSHELL;
	node->subshell = sub;
	return (node);
}

void	ast_clear(t_ast **root)
{
	t_ast	*node;
	int		i;

	if (!root || !(*root))
		return ;
	node = *root;
	if (node->type == TOKEN_PIPELINE)
	{
		i = 0;
		while (i < node->pipeline.count)
		{
			ast_clear(&node->pipeline.cmds[i]);
			i++;
		}
		free(node->pipeline.cmds);
	}
	else if (node->type == TOKEN_LOGICAL_EXPRESSION)
	{
		ast_clear(&node->logical.left);
		ast_clear(&node->logical.right);
	}
	else if (node->type == TOKEN_SUBSHELL)
		ast_clear(&node->subshell);
	free(node);
	*root = NULL;
}
