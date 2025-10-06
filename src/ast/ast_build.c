#include "ast.h"

static t_ast	*parse_logical_expr(t_list2 **tokens);
static t_ast	*parse_pipeline(t_list2 **tokens);
static t_ast	*parse_subshell(t_list2 **tokens);
static t_ast	*parse_simple_command_or_subshell(t_list2 **tokens);

t_ast	*ast_build(t_list2 *tokens)
{
	return (parse_logical_expr(&tokens));
}

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

static t_ast	*parse_pipeline(t_list2 **tokens)
{
	t_list2	*save;
	t_token	*tok;
	t_ast	**cmds;
	size_t	count;
	size_t	i;

	save = *tokens;
	count = 0;
	while (save)
	{
		tok = (t_token *)save->content;
		if (tok->type == TOKEN_COMMAND ||
			(tok->type == TOKEN_SUBSHELL && ft_strcmp(tok->data, "(") == 0))
			count++;
		if (tok->type != TOKEN_PIPELINE &&
			tok->type != TOKEN_COMMAND &&
			tok->type != TOKEN_SUBSHELL)
			break ;
		save = save->next;
	}
	if (count == 0)
		return (NULL);
	else if (count == 1)
	{
		t_ast *single = parse_simple_command_or_subshell(tokens);
		return (single);
	}
	cmds = ft_calloc(count + 1, sizeof(t_ast *));
	if (!cmds)
		return (NULL);

	i = 0;
	while (*tokens)
	{
		tok = (t_token *)(*tokens)->content;
		if (tok->type == TOKEN_COMMAND ||
			(tok->type == TOKEN_SUBSHELL && ft_strcmp(tok->data, "(") == 0))
		{
			cmds[i++] = parse_simple_command_or_subshell(tokens);
			continue;
		}
		else if (tok->type == TOKEN_PIPELINE)
			*tokens = (*tokens)->next;
		else
			break;
	}
	cmds[i] = NULL;
	return (ast_new_pipeline(cmds, count));
}

static t_ast	*parse_subshell(t_list2 **tokens)
{
	t_ast	*sub;
	t_token	*tok;

	if (!*tokens)
		return (NULL);
	*tokens = (*tokens)->next;
	sub = parse_logical_expr(tokens);
	if (!sub)
		return (NULL);
	if (!*tokens)
	{
		printf("Syntax error: missing closing parenthesis\n");
		return (NULL);
	}
	tok = (t_token *)(*tokens)->content;
	if (tok->type != TOKEN_SUBSHELL || ft_strcmp(tok->data, ")") != 0)
	{
		printf("Syntax error: missing closing parenthesis\n");
		return (NULL);
	}
	*tokens = (*tokens)->next;
	return (ast_new_subshell(sub));
}

static t_ast	*parse_simple_command_or_subshell(t_list2 **tokens)
{
	t_token		*tok;
	t_command	*cmd;

	if (!*tokens)
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
