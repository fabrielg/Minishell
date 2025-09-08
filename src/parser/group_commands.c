#include "tokens.h"

static void	flush_command(t_list2 **result, t_command **current)
{
	if (*current)
	{
		ft_lstadd_back2(result, ft_lstnew2(token_create_command(*current)));
		*current = NULL;
	}
}

static void	handle_word_or_redir(t_command **current, t_token *tok)
{
	if (!*current)
		*current = command_create();
	if (tok->type == TOKEN_WORD)
	{
		ft_lstadd_back2(&(*current)->args, ft_lstnew2(tok->data));
		tok->data = NULL;
	}
	else if (tok->type == TOKEN_REDIRECT)
	{
		ft_lstadd_back2(&(*current)->redirects, ft_lstnew2(tok->data));
		tok->data = NULL;
	}
}

static void	handle_other_token(t_list2 **result, t_command **current,
	t_list2 *tmp, t_token *tok)
{
	flush_command(result, current);
	ft_lstadd_back2(result, ft_lstnew2(tok));
	tmp->content = NULL;
}

t_list2	*group_commands(t_list2 *tokens)
{
	t_list2		*result;
	t_list2		*tmp;
	t_command	*current;
	t_token		*tok;

	result = NULL;
	current = NULL;
	tmp = tokens;
	while (tmp)
	{
		tok = (t_token *)tmp->content;
		if (tok->type == TOKEN_WORD || tok->type == TOKEN_REDIRECT)
			handle_word_or_redir(&current, tok);
		else
			handle_other_token(&result, &current, tmp, tok);
		tmp = tmp->next;
	}
	flush_command(&result, &current);
	ft_lstclear2(&tokens, token_destroy);
	return (result);
}
