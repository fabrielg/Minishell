#include "tokens.h"

t_token	*token_create(t_token_type type, void *data)
{
	t_token	*token;

	token = NULL;
	if (type == TOKEN_WORD)
		token = token_create_word((t_word *) data);
	else if (type == TOKEN_REDIRECT)
		token = token_create_redir((t_redirect *) data);
	/*else if (type == TOKEN_COMMAND)
		token = token_create_command(data->command->args,
				data->command->arg_count, data->command->redirects,
				data->command->redirect_count);
	else if (type == TOKEN_SUBSHELL)
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
	else
		return ;
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

t_list2	*parse_contents(char **contents)
{
	t_list2			*tokens;
	void			*data;
	int				i;
	t_token_type	type;

	tokens = NULL;
	i = 0;
	while (contents[i])
	{
		type = detect_type(contents[i]);
		if (type == TOKEN_WORD)
		{
			data = token_parse_word(contents[i]);
			ft_lstadd_back2(&tokens, ft_lstnew2(token_create(type, data)));
		}
		else if (type == TOKEN_REDIRECT)
		{
			data = token_parse_redir(contents, &i);
			ft_lstadd_back2(&tokens, ft_lstnew2(token_create_redir(data)));
		}
		i++;
	}
	return (tokens);
}
