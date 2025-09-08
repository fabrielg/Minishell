#include "tokens.h"

t_token	*token_create(t_token_type type, void *data)
{
	t_token	*token;

	token = NULL;
	if (type == TOKEN_WORD)
		token = token_create_word((t_word *) data);
	else if (type == TOKEN_REDIRECT)
		token = token_create_redir((t_redirect *) data);
	else if (type == TOKEN_COMMAND)
		token = token_create_command((t_command *) data);
	/*else if (type == TOKEN_SUBSHELL)
		token = token_create_subshell(data->subshell->content,
				data->subshell->redirects, data->subshell->redirect_count);
	else if (type == TOKEN_PIPELINE)
		token = token_create_pipeline(data->pipeline->commands,
				data->pipeline->command_count);
	else if (type == TOKEN_LOGICAL_EXPRESSION)
		token = token_create_logic_exp(data->logical_expr->op,
				data->logical_expr->left, data->logical_expr->right);*/
	return (token);
}

void	token_clear(t_token **tokens, int token_count)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (i < token_count)
	{
		token_destroy(tokens[i]);
		i++;
	}
	free(tokens);
}

void	token_destroy(void *content)
{
	t_token	*token;

	token = (t_token *) content;
	if (!token)
		return ;
	if (token->type == TOKEN_WORD)
		token_destroy_word(token->data);
	else if (token->type == TOKEN_REDIRECT)
		token_destroy_redir(token->data);
	else if (token->type == TOKEN_COMMAND)
		token_destroy_command(token->data);
	else
		token_destroy_word(token->data);
	free(token);
}

static t_token_type	detect_type(char *s)
{
	if (!ft_strcmp(s, "|"))
		return (TOKEN_PIPELINE);
	if (!ft_strcmp(s, "&&") || !ft_strcmp(s, "||"))
		return (TOKEN_LOGICAL_EXPRESSION);
	if (!ft_strcmp(s, "(") || !ft_strcmp(s, ")"))
		return (TOKEN_SUBSHELL);
	if (!ft_strcmp(s, "<") || !ft_strcmp(s, ">")
		|| !ft_strcmp(s, "<<") || !ft_strcmp(s, ">>"))
		return (TOKEN_REDIRECT);
	return (TOKEN_WORD);
}

static t_token	*token_new_word(const char *s)
{
	t_token	*token;
	t_word	*w;

	w = token_parse_word((char *)s);
	if (!w)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
	{
		token_destroy_word(w);
		return (NULL);
	}
	token->type = TOKEN_WORD;
	token->data = w;
	return (token);
}

static t_token	*token_new_redirect_from_contents(char **contents, int *i)
{
	t_token		*token;
	t_redirect	*r;

	r = token_parse_redir(contents, i);
	if (!r)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
	{
		token_destroy_redir(r);
		return (NULL);
	}
	token->type = TOKEN_REDIRECT;
	token->data = r;
	return (token);
}

static t_token	*token_new_op(const char *s, t_token_type type)
{
	t_token	*token;
	t_word	*w;

	w = token_parse_word((char *)s);
	if (!w)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
	{
		token_destroy_word(w);
		return (NULL);
	}
	token->type = type;
	token->data = w;
	return (token);
}

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
			token = token_new_redirect_from_contents(contents, &i);
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

static t_command	*command_create(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirects = NULL;
	return (cmd);
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
	return (result);
}
