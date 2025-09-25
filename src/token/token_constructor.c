#include "tokens.h"

t_token	*token_new_op(const char *s, t_token_type type)
{
	t_token	*token;
	char	*w;

	w = ft_strdup(s);
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

t_token_type	detect_type(char *s)
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

static void	token_display(t_token *token)
{
	char	*data;

	data = (char *) token->data;
	if (token->type == TOKEN_COMMAND)
		token_display_command(token->data);
	else if (token->type == TOKEN_LOGICAL_EXPRESSION)
		printf("TOKEN_LOGICAL_EXPRESSION=[%s]\n", data);
	else if (token->type == TOKEN_PIPELINE)
		printf("TOKEN_PIPELINE=[%s]\n", data);
	else if (token->type == TOKEN_REDIRECT)
		token_display_redirect(token->data);
	else if (token->type == TOKEN_SUBSHELL)
		printf("TOKEN_SUBSHELL=[%s]\n", data);
	else if (token->type == TOKEN_WORD)
		token_display_word(data);
}

void	tokens_display(t_list2 *tokens)
{
	t_list2			*tmp;
	t_token			*current_token;

	tmp = tokens;
	while (tmp)
	{
		current_token = (t_token *) tmp->content;
		token_display(current_token);
		printf("\n");
		tmp = tmp->next;
	}
}
