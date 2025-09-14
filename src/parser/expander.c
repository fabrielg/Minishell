#include "envp.h"
#include "libft.h"
#include "tokens.h"
#include "lexer.h"

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

static void	expand_exit_code(char **new_arg, int exit_code)
{
	char	*tmp;

	tmp = ft_itoa(exit_code);
	if (!tmp)
		return ;
	ft_strappend(new_arg, tmp);
	free(tmp);
}

static void	append_segment(char **new_arg, char *arg, int start, int end)
{
	char	*tmp;

	if (end > start)
	{
		tmp = ft_substr(arg, start, end - start);
		if (!tmp)
			return ;
		ft_strappend(new_arg, tmp);
		free(tmp);
	}
}

static int	handle_exit_code(char **new_arg, int exit_code, int i)
{
	expand_exit_code(new_arg, exit_code);
	return (i + 2);
}

static int	handle_variable(char **new_arg, char *arg, int i, t_mst *env)
{
	int		start;
	char	*key;
	t_mst	*node;

	start = ++i;
	while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
		i++;
	if (i > start)
	{
		key = ft_substr(arg, start, i - start);
		node = mst_get_node(env, key);
		if (node && node->dic && node->dic->value)
			ft_strappend(new_arg, node->dic->value);
		free(key);
	}
	else
		ft_strappend(new_arg, "$");
	return (i);
}

void	expand_arg(char **arg_ptr, t_mst *env, int exit_code)
{
	char	*arg;
	char	*new_arg;
	int		i;
	int		seg_start;

	arg = *arg_ptr;
	if (!arg)
		return ;
	new_arg = NULL;
	i = 0;
	seg_start = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			append_segment(&new_arg, arg, seg_start, i);
			if (arg[i + 1] == '?')
				i = handle_exit_code(&new_arg, exit_code, i);
			else
				i = handle_variable(&new_arg, arg, i, env);
			seg_start = i;
		}
		else
			i++;
	}
	append_segment(&new_arg, arg, seg_start, i);
	free(*arg_ptr);
	*arg_ptr = new_arg;
}

void	expand_command(t_command *cmd, t_mst *env, int exit_code)
{
	t_list2	*redir;
	bool	is_expandable;
	int		i;

	i = 0;
	while (i < cmd->argc)
	{
		is_expandable = is_expandable_word(cmd->args[i]);
		unquote(&cmd->args[i]);
		if (is_expandable)
			expand_arg(&cmd->args[i], env, exit_code);
		i++;
	}
	redir = cmd->redirects;
	while (redir)
	{
		is_expandable = is_expandable_word(((t_redirect *) redir->content)->file);
		unquote(&((t_redirect *) redir->content)->file);
		if (is_expandable)
			expand_arg(&((t_redirect *) redir->content)->file, env, exit_code);
		redir = redir->next;
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
