#include "envp.h"

static void	expand_exit_code(char **new_arg, int exit_code)
{
	char	*tmp;

	tmp = ft_itoa(exit_code);
	if (!tmp)
		return ;
	ft_strappend(new_arg, tmp);
	free(tmp);
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
		if (node && node->dic.value)
			ft_strappend(new_arg, node->dic.value);
		free(key);
	}
	else
		ft_strappend(new_arg, "$");
	return (i);
}

void	append_segment(char **new_arg, char *arg, int start, int end)
{
	char	*tmp;

	if (*new_arg == NULL)
		*new_arg = ft_strdup("");
	if (end > start)
	{
		tmp = ft_substr(arg, start, end - start);
		if (!tmp)
			return ;
		ft_strappend(new_arg, tmp);
		free(tmp);
	}
}

void	expand_checker(char *args[2], int *i, int exit_code, t_mst *env)
{
	if (args[0][(*i) + 1] == '?')
		*i = handle_exit_code(&args[1], exit_code, *i);
	else
		*i = handle_variable(&args[1], args[0], *i, env);
}
