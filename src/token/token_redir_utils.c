#include "tokens.h"

t_token	*token_create_redir(t_redirect_type type, t_word *file, int fd)
{
	t_token		*token;
	t_redirect	*redir;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	redir = (t_redirect *) malloc(sizeof(t_redirect));
	if (!redir)
		return (free(token), NULL);
	redir->type = type;
	redir->file = file;
	redir->fd = fd;
	token->type = TOKEN_REDIRECT;
	token->data.redirect = redir;
	return (token);
}

void	token_clear_redir(t_redirect **redir, int rdc)
{
	int	i;

	if (!redir)
		return ;
	i = 0;
	while (i < rdc)
	{
		token_destroy_redir(redir[i]);
		i++;
	}
	free(redir);
}

void	token_destroy_redir(t_redirect *redir)
{
	if (!redir)
		return ;
	token_destroy_word(redir->file);
	free(redir);
}