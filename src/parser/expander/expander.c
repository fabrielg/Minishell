#include "envp.h"
#include "libft.h"
#include "tokens.h"
#include "expander.h"

static void	unquote(char **s)
{
	size_t	s_len;
	char	*new_s;

	if (!s || !(*s))
		return ;
	s_len = ft_strlen(*s);
	if (s_len < 2)
		return ;
	if (((*s)[0] == '"' && (*s)[s_len - 1] == '"')
		|| ((*s)[0] == '\'' && (*s)[s_len - 1] == '\''))
	{
		new_s = ft_substr(*s, 1, s_len - 2);
		free(*s);
		*s = new_s;
	}
}

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
	bool		is_expandable;
	int			i;

	i = 0;
	while (i < cmd->argc)
	{
		is_expandable = is_expandable_word(cmd->args[i]);
		unquote(&cmd->args[i]);
		if (is_expandable)
			expand_arg(&cmd->args[i], env, exit_code);
		i++;
	}
	redirs = cmd->redirects;
	while (redirs)
	{
		redir = (t_redirect *) redirs->content;
		is_expandable = is_expandable_word(redir->file);
		unquote(&redir->file);
		if (is_expandable)
			expand_arg(&redir->file, env, exit_code);
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
