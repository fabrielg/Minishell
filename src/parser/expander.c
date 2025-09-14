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

static void	expand_arg(char **arg_ptr, t_mst *env, int exit_code)
{
	char	*arg;
	char	*new_arg;
	int		i;
	int		start;
	char	*key;
	t_mst	*node;

	arg = *arg_ptr;
	if (!arg)
		return ;
	new_arg = ft_strdup("");
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			if (arg[i + 1] == '?')
			{
				ft_strappend(&new_arg, ft_itoa(exit_code));
				i += 2;
				continue;
			}
			start = ++i;
			while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
				i++;
			if (i > start)
			{
				key = ft_substr(arg, start, i - start);
				node = mst_get_node(env, key);
				if (node && node->dic && node->dic->value)
					ft_strappend(&new_arg, node->dic->value);
				free(key);
				continue;
			}
			ft_strappend(&new_arg, "$");
		}
		else
		{
			ft_strappend(&new_arg, ft_substr(arg, i, 1));
			i++;
		}
	}
	free(*arg_ptr);
	*arg_ptr = new_arg;
}

void	expand_command(t_command *cmd, t_mst *env, int exit_code)
{
	bool	is_expandable;

	for (int i = 0; i < cmd->argc; i++)
	{
		is_expandable = is_expandable_word(cmd->args[i]);
		unquote(&cmd->args[i]);
		printf("cmd: [%s]\n", cmd->args[i]);
		if (is_expandable)
			expand_arg(&cmd->args[i], env, exit_code);
	}
	t_list2	*redir = cmd->redirects;
	while (redir)
	{
		is_expandable = is_expandable_word(((t_redirect *) redir->content)->file);
		unquote(&((t_redirect *) redir->content)->file);
		printf("redir: [%s]\n", ((t_redirect *) redir->content)->file);
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
