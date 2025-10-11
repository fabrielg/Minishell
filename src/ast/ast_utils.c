#include "ast.h"

/**
 * @brief Creates a new AST node representing a command.
 * @return Newly allocated AST node, or NULL on failure
 */
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

/**
 * @brief Creates a new AST node representing a pipeline of commands.
 * @return Newly allocated AST node, or NULL on failure
 */
t_ast	*ast_new_pipeline(t_ast **cmds, size_t count)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = TOKEN_PIPELINE;
	node->s_pipeline.count = count;
	node->s_pipeline.cmds = cmds;
	return (node);
}

/**
 * @brief Creates a new AST node representing a logical expression (&& or ||).
 * @return Newly allocated AST node, or NULL on failure
 */
t_ast	*ast_new_logical(t_logical_op op, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = TOKEN_LOGICAL_EXPRESSION;
	node->s_logical.op = op;
	node->s_logical.left = left;
	node->s_logical.right = right;
	return (node);
}

/**
 * @brief Creates a new AST node representing a subshell.
 * @return Newly allocated AST node, or NULL on failure
 */
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

/**
 * @brief Recursively frees an AST and all its children.
 */
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
		while (i < node->s_pipeline.count)
		{
			ast_clear(&node->s_pipeline.cmds[i]);
			i++;
		}
		free(node->s_pipeline.cmds);
	}
	else if (node->type == TOKEN_LOGICAL_EXPRESSION)
	{
		ast_clear(&node->s_logical.left);
		ast_clear(&node->s_logical.right);
	}
	else if (node->type == TOKEN_SUBSHELL)
		ast_clear(&node->subshell);
	free(node);
	*root = NULL;
}
