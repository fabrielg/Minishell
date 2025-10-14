#include "ast.h"

static t_ast	*parse_logical_expr(t_list2 **tokens);
static t_ast	*parse_subshell(t_list2 **tokens);

/**
 * @brief Builds an AST from a token list.
 * @return Root AST node
 */
t_ast	*ast_build(t_list2 *tokens)
{
	if (!tokens)
		return (NULL);
	return (parse_logical_expr(&tokens));
}

/**
 * @brief Parses logical expressions (&&, ||) from tokens.
 * @return AST node representing the logical expression
 */
static t_ast	*parse_logical_expr(t_list2 **tokens)
{
	t_ast			*left;
	t_ast			*right;
	t_token			*tok;
	t_logical_op	op;

	left = parse_pipeline(tokens);
	while (*tokens)
	{
		tok = (t_token *)(*tokens)->content;
		if (tok->type != TOKEN_LOGICAL_EXPRESSION)
			break ;
		op = LOGICAL_OR;
		if (ft_strcmp(tok->data, "&&") == 0)
			op = LOGICAL_AND;
		*tokens = (*tokens)->next;
		right = parse_pipeline(tokens);
		left = ast_new_logical(op, left, right);
	}
	return (left);
}

/**
 * @brief Parses a subshell expression enclosed in parentheses.
 * @return AST node representing the subshell, or NULL on failure
 */
static t_ast	*parse_subshell(t_list2 **tokens)
{
	t_ast	*sub;

	if (!*tokens)
		return (NULL);
	*tokens = (*tokens)->next;
	sub = parse_logical_expr(tokens);
	if (!sub || !*tokens)
		return (NULL);
	*tokens = (*tokens)->next;
	return (ast_new_subshell(sub));
}

/**
 * @brief Parses either a simple command or a subshell from tokens.
 * @return AST node for command or subshell, or NULL on unexpected token
 */
t_ast	*parse_simple_command_or_subshell(t_list2 **tokens)
{
	t_token		*tok;
	t_command	*cmd;

	if (!tokens || !*tokens)
		return (NULL);
	tok = (t_token *)(*tokens)->content;
	if (tok->type == TOKEN_SUBSHELL && ft_strcmp(tok->data, "(") == 0)
		return (parse_subshell(tokens));
	else if (tok->type == TOKEN_COMMAND)
	{
		cmd = (t_command *)tok->data;
		*tokens = (*tokens)->next;
		return (ast_new_command(cmd));
	}
	else
	{
		printf("Unexpected token: %s\n", (char *)tok->data);
		return (NULL);
	}
}
