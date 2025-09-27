#include "ast.h"

static void	print_indent(int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
}

static char	*get_redir_type(t_redirect_type type)
{
	char	*type_str;

	type_str = "UNKNOWN";
	if (type == REDIRECT_INPUT)
		type_str = "INPUT <";
	else if (type == REDIRECT_OUTPUT)
		type_str = "OUTPUT >";
	else if (type == REDIRECT_HEREDOC)
		type_str = "HEREDOC <<";
	else if (type == REDIRECT_APPEND)
		type_str = "APPEND >>";
	else if (type == REDIRECT_AMBIGUOUS)
		type_str = "ambigous redirect";
	return (type_str);
}

static void	ast_display_cmd(t_command *cmd, int depth)
{
	t_redirect	*redir;
	int			i;

	i = 0;
	printf("COMMAND: ");
	while (i < cmd->argc)
		printf("%s ", cmd->args[i++]);
	printf("\n");
	print_indent(depth);
	while (cmd->redirects)
	{
		redir = (t_redirect *) cmd->redirects->content;
		printf("%s %s  ", get_redir_type(redir->type), redir->file);
		cmd->redirects = cmd->redirects->next;
	}
	printf("\n");
}

void	ast_display(t_ast *node, int depth)
{
	if (!node)
		return ;
	print_indent(depth);
	if (node->type == TOKEN_COMMAND)
		ast_display_cmd(node->cmd, depth);
	else if (node->type == TOKEN_PIPELINE)
	{
		printf("PIPELINE:\n");
		ast_display(node->pipeline.left, depth + 1);
		ast_display(node->pipeline.right, depth + 1);
	}
	else if (node->type == TOKEN_LOGICAL_EXPRESSION)
	{
		if (node->logical.op == LOGICAL_AND)
			printf("LOGICAL: &&\n");
		else
			printf("LOGICAL: ||\n");
		ast_display(node->logical.left, depth + 1);
		ast_display(node->logical.right, depth + 1);
	}
	else if (node->type == TOKEN_SUBSHELL)
	{
		printf("SUBSHELL:\n");
		ast_display(node->subshell, depth + 1);
	}
}
