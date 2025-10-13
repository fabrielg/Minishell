#include "tokens.h"

/**
 * @brief Create a redirection structure from token contents.
 * @return Pointer to the new redirection or NULL on failure.
 */
t_redirect	*parse_redir(char **contents, int *i)
{
	t_redirect	*r;

	r = ft_calloc(1, sizeof(t_redirect));
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
		r->file = ft_strdup(contents[++(*i)]);
	else
		r->file = NULL;
	return (r);
}

/**
 * @brief Create a redirection token from contents.
 * @return Pointer to the new token or NULL on failure.
 */
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

/**
 * @brief Free a redirection structure.
 */
void	token_destroy_redir(void *data)
{
	t_redirect	*redir;

	redir = (t_redirect *) data;
	if (!redir)
		return ;
	if (redir->file)
		free(redir->file);
	if (redir->options)
		free(redir->options);
	free(redir);
}

/**
 * @brief Retrieve a redirection structure from a token's data.
 * @return Pointer to the redirection.
 */
t_redirect	*get_redir(void *data)
{
	t_redirect	*r;

	r = (t_redirect *) data;
	return (r);
}

/**
 * @brief Display a redirection's information.
 */
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
	else if (redir->type == REDIRECT_AMBIGUOUS)
		type_str = "ambigous redirect";
	printf("Redirect: %s, options: %s,", type_str, redir->options);
	printf(" fd=%d, file=", redir->fd);
	token_display_word(redir->file);
	printf("\n");
}
