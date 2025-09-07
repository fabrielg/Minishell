#include "tokens.h"

/*t_token	*token_create_subshell(t_token *content, t_redirect **redir, int rdc)
{
	t_token		*token;
	t_subshell	*subshell;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	subshell = (t_subshell *) malloc(sizeof(t_subshell));
	if (!subshell)
		return (free(token), NULL);
	subshell->content = content;
	subshell->redirects = redir;
	subshell->redirect_count = rdc;
	token->type = TOKEN_SUBSHELL;
	token->data.subshell = subshell;
	return (token);
}

void	token_destroy_subshell(t_subshell *subshell)
{
	if (!subshell)
		return ;
	token_destroy(subshell->content);
	token_clear_redir(subshell->redirects, subshell->redirect_count);
	free(subshell);
}*/