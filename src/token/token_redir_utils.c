#include "tokens.h"

t_token	*token_create_redir(t_redirect *redir)
{
	t_token		*token;

	if (!redir)
		return (NULL);
	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = TOKEN_REDIRECT;
	token->data = redir;
	return (token);
}

// static t_redirect_type	get_redir_type(char **symbol)
// {
// 	if ((*symbol)[0] == '<' && (*symbol)[1] == '<')
// 		return (++(*symbol), REDIRECT_HEREDOC);
// 	else if ((*symbol)[0] == '<')
// 		return (REDIRECT_INPUT);
// 	else if ((*symbol)[0] == '>' && (*symbol)[1] == '>')
// 		return (++(*symbol), REDIRECT_APPEND);
// 	return (REDIRECT_OUTPUT);
// }

t_redirect	*token_parse_redir(char **contents, int *i)
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
		r->file = token_parse_word(contents[++(*i)]);
	else
		r->file = NULL;
	return (r);
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