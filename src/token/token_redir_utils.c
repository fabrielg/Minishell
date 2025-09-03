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
	token->data.redirect = redir;
	return (token);
}

static t_redirect_type	get_redir_type(char **symbol)
{
	if ((*symbol)[0] == '<' && (*symbol)[1] == '<')
		return (++(*symbol), REDIRECT_HEREDOC);
	else if ((*symbol)[0] == '<')
		return (REDIRECT_INPUT);
	else if ((*symbol)[0] == '>' && (*symbol)[1] == '>')
		return (++(*symbol), REDIRECT_APPEND);
	return (REDIRECT_OUTPUT);
}

t_token_data	token_parse_redir(char *content)
{
	t_token_data	data;
	t_redirect		*redir;
	char			*symbol;
	t_token_data	file;

	data.redirect = NULL;
	redir = (t_redirect *) malloc(sizeof(t_redirect));
	if (!redir)
		return (data);
	redir->fd = -1;
	symbol = ft_strchrset(content, "<>");
	if (!symbol || symbol[0] == 0)
		return (free(redir), data);
	redir->type = get_redir_type(&symbol);
	symbol = ft_strnotchr(symbol + 1, ' ');
	file = token_parse_word(symbol);
	if (!file.word)
		return (free(redir), data);
	redir->file = file.word;
	data.redirect = redir;
	return (data);
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