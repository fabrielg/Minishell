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
	t_list2		*redirs;
	t_redirect	*redir;
	int			i;

	i = 0;
	printf("COMMAND: ");
	while (i < cmd->argc)
		printf("%s ", cmd->args[i++]);
	printf("\n");
	print_indent(depth);
	redirs = cmd->redirects;
	while (redirs)
	{
		redir = (t_redirect *) redirs->content;
		printf("%s %s  ", get_redir_type(redir->type), redir->file);
		redirs = redirs->next;
	}
	print_indent(depth);
	printf("pipes[0] = %d pipes[1] = %d\n", cmd->pipes[0], cmd->pipes[1]);
}

static void	ast_display_aux(t_ast *node, int depth, const char logicals[2][2])
{
	int	i;

	if (!node)
		return ;
	print_indent(depth);
	if (node->type == TOKEN_COMMAND)
		ast_display_cmd(node->cmd, depth);
	else if (node->type == TOKEN_PIPELINE)
	{
		printf("PIPELINE:\n");
		i = -1;
		while (++i < node->pipeline.count)
			ast_display_aux(node->pipeline.cmds[i], depth + 1, logicals);
	}
	else if (node->type == TOKEN_LOGICAL_EXPRESSION)
	{
		printf("LOGICAL: %.2s\n", logicals[node->logical.op == LOGICAL_AND]);
		ast_display_aux(node->logical.left, depth + 1, logicals);
		ast_display_aux(node->logical.right, depth + 1, logicals);
	}
	else if (node->type == TOKEN_SUBSHELL)
	{
		printf("SUBSHELL:\n");
		ast_display_aux(node->subshell, depth + 1, logicals);
	}
}

void	ast_display(t_ast *node)
{
	const char	logicals[2][2] = {"||", "&&"};
	t_ast		*tmp;

	tmp = node;
	ast_display_aux(tmp, 0, logicals);
}
