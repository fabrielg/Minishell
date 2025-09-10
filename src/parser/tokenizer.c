#include "tokens.h"

static int	add_token_safe(t_list2 **tokens, t_token *token)
{
	if (!token)
		return (ft_lstclear2(tokens, token_destroy), 0);
	ft_lstadd_back2(tokens, ft_lstnew2(token));
	return (1);
}

static int	handle_redirect(t_list2 **tokens, char **contents, int *i)
{
	t_token	*token;

	token = token_new_redir(contents, i);
	return (add_token_safe(tokens, token));
}

static int	handle_operator(t_list2 **tokens, char *content, t_token_type type)
{
	t_token	*token;

	token = token_new_op(content, type);
	return (add_token_safe(tokens, token));
}

t_list2	*tokenize(char **contents)
{
	t_list2			*tokens;
	t_token_type	type;
	int				i;

	tokens = NULL;
	i = 0;
	while (contents[i])
	{
		type = detect_type(contents[i]);
		if (type != TOKEN_REDIRECT && !handle_operator(&tokens, contents[i], type))
			return (NULL);
		else if (type == TOKEN_REDIRECT
			&& !handle_redirect(&tokens, contents, &i))
			return (NULL);
		i++;
	}
	return (tokens);
}
