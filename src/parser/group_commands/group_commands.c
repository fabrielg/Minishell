#include "tokens.h"
#include "parser.h"

static int	count_args(t_list2 *tmp)
{
	int		count;
	t_token	*tok;

	count = 0;
	while (tmp)
	{
		tok = (t_token *)tmp->content;
		if (tok->type == TOKEN_WORD)
			count++;
		else if (tok->type != TOKEN_REDIRECT)
			break ;
		tmp = tmp->next;
	}
	return (count);
}

static t_command	*command_create_with_args(int argc)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = malloc(sizeof(char *) * (argc + 1));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	cmd->argc = 0;
	cmd->redirects = NULL;
	cmd->args[0] = NULL;
	cmd->pipes[0] = STDIN_FILENO;
	cmd->pipes[1] = STDOUT_FILENO;
	return (cmd);
}

static void	handle_word_or_redir(t_command *cmd, t_token *tok)
{
	if (tok->type == TOKEN_WORD)
	{
		cmd->args[cmd->argc++] = tok->data;
		cmd->args[cmd->argc] = NULL;
		tok->data = NULL;
	}
	else if (tok->type == TOKEN_REDIRECT)
	{
		ft_lstadd_back2(&cmd->redirects, ft_lstnew2(tok->data));
		tok->data = NULL;
	}
}

static int	process_token(t_list2 **res, t_command **cur, t_list2 *tmp)
{
	t_token	*tok;
	int		argc;

	tok = (t_token *)tmp->content;
	if (tok->type == TOKEN_WORD || tok->type == TOKEN_REDIRECT)
	{
		if (!*cur)
		{
			argc = count_args(tmp);
			*cur = command_create_with_args(argc);
			if (!*cur)
				return (1);
		}
		handle_word_or_redir(*cur, tok);
	}
	else
	{
		flush_command(res, cur);
		ft_lstadd_back2(res, ft_lstnew2(tok));
		tmp->content = NULL;
	}
	return (0);
}

t_list2	*group_commands(t_list2 *tokens)
{
	t_list2		*result;
	t_list2		*tmp;
	t_command	*current;

	result = NULL;
	tmp = tokens;
	current = NULL;
	while (tmp)
	{
		if (process_token(&result, &current, tmp))
		{
			ft_lstclear2(&tokens, token_destroy);
			return (NULL);
		}
		tmp = tmp->next;
	}
	flush_command(&result, &current);
	ft_lstclear2(&tokens, token_destroy);
	return (result);
}
