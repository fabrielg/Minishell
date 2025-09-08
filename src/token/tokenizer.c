#include "tokens.h"

t_list2	*tokenize(char **contents)
{
	t_list2			*tokens = NULL;
	t_token			*token;
	t_token_type	type;
	int				i;

	i = 0;
	while (contents[i])
	{
		type = detect_type(contents[i]);
		if (type == TOKEN_WORD)
		{
			token = token_new_word(contents[i]);
			if (!token)
				return (ft_lstclear2(&tokens, token_destroy), NULL);
			ft_lstadd_back2(&tokens, ft_lstnew2(token));
		}
		else if (type == TOKEN_REDIRECT)
		{
			token = token_new_redir(contents, &i);
			if (!token)
				return (ft_lstclear2(&tokens, token_destroy), NULL);
			ft_lstadd_back2(&tokens, ft_lstnew2(token));
		}
		else
		{
			token = token_new_op(contents[i], type);
			if (!token)
				return (ft_lstclear2(&tokens, token_destroy), NULL);
			ft_lstadd_back2(&tokens, ft_lstnew2(token));
		}
		i++;
	}
	return (tokens);
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
		if (tok->type == TOKEN_WORD)
		{
			if (!current)
				current = command_create();
			ft_lstadd_back2(&current->args, ft_lstnew2(tok->data));
			tok->data = NULL;
		}
		else if (tok->type == TOKEN_REDIRECT)
		{
			if (!current)
				current = command_create();
			ft_lstadd_back2(&current->redirects, ft_lstnew2(tok->data));
			tok->data = NULL;
		}
		else
		{
			if (current)
			{
				ft_lstadd_back2(&result, ft_lstnew2(token_create_command(current)));
				current = NULL;
			}
			ft_lstadd_back2(&result, ft_lstnew2(tok));
			tmp->content = NULL;
		}
		tmp = tmp->next;
	}
	if (current)
		ft_lstadd_back2(&result, ft_lstnew2(token_create_command(current)));
	ft_lstclear2(&tokens, token_destroy);
	tokens = result;
	return (result);
}
