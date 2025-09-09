#include "tokens.h"

t_redirect	*parse_redir(char **contents, int *i)
{
	t_redirect	*r;

	r = malloc(sizeof(t_redirect));
	if (!r)
		return (NULL);
	r->fd = -1;
	if (!ft_strcmp(contents[*i], "<"))
		r->type = REDIRECT_INPUT;
	else if (!ft_strcmp(contents[*i], ">"))
		r->type = REDIRECT_OUTPUT;
	else if (!ft_strcmp(contents[*i], ">>"))
		r->type = REDIRECT_APPEND;
	else
		r->type = REDIRECT_HEREDOC;
	if (contents[(*i) + 1])
		r->file = parse_word(contents[++(*i)]);
	else
		r->file = NULL;
	return (r);
}

t_token	*token_new_redir(char **contents, int *i)
{
	t_token		*token;
	t_redirect	*r;

	r = parse_redir(contents, i);
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

void	token_destroy_redir(void *data)
{
	t_redirect	*redir;

	redir = (t_redirect *) data;
	if (!redir)
		return ;
	token_destroy_word(redir->file);
	free(redir);
}

t_redirect	*get_redir(void *data)
{
	t_redirect	*r;

	r = (t_redirect *) data;
	return (r);
}

void	token_display_redirect(t_redirect *redir)
{
	const char	*type_str;

	if (!redir)
		return ;
	type_str = "UNKNOWN";
	if (redir->type == REDIRECT_INPUT)
		type_str = "INPUT <";
	else if (redir->type == REDIRECT_OUTPUT)
		type_str = "OUTPUT >";
	else if (redir->type == REDIRECT_HEREDOC)
		type_str = "HEREDOC <<";
	else if (redir->type == REDIRECT_APPEND)
		type_str = "APPEND >>";
	printf("Redirect: %s, fd=%d, file=", type_str, redir->fd);
	token_display_word(redir->file);
	printf("\n");
}
