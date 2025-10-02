#include "envp.h"
#include "libft.h"
#include "tokens.h"
#include "expander.h"
#include "smart_split.h"

void	expand_arg(char **arg_ptr, t_mst *env, int exit_code)
{
	char	*args[2];
	int		i;
	int		seg_start;

	args[0] = *arg_ptr;
	if (!args[0])
		return ;
	args[1] = NULL;
	i = 0;
	seg_start = 0;
	while (args[0][i])
	{
		if (args[0][i] == '$')
		{
			append_segment(&args[1], args[0], seg_start, i);
			expand_checker(args, &i, exit_code, env);
			seg_start = i;
		}
		else
			i++;
	}
	append_segment(&args[1], args[0], seg_start, i);
	free(*arg_ptr);
	*arg_ptr = args[1];
}

void	expand_command(t_command *cmd, t_mst *env, int exit_code)
{
	t_list2		*redirs;
	t_redirect	*redir;
	int			i;

	i = 0;
	while (i < cmd->argc)
	{
		if (is_expandable_word(cmd->args[i]))
			expand_arg(&cmd->args[i], env, exit_code);
		token_unquote(&cmd->args[i]);
		i++;
	}
	redirs = cmd->redirects;
	while (redirs)
	{
		redir = (t_redirect *) redirs->content;
		if (is_expandable_word(redir->file) && redir->type != REDIRECT_HEREDOC)
			expand_arg(&redir->file, env, exit_code);
		token_unquote(&redir->file);
		redirs = redirs->next;
	}
}

void	expander(t_list2 *tokens, t_mst *env, int exit_code)
{
	t_list2	*tmp;
	t_token	*tok;

	tmp = tokens;
	while (tmp)
	{
		tok = (t_token *)tmp->content;
		if (tok->type == TOKEN_COMMAND)
			expand_command(tok->data, env, exit_code);
		tmp = tmp->next;
	}
}
