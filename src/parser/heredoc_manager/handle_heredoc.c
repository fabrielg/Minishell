#include "minishell.h"
#include "parser.h"

//[GUETTER]____________________________

t_list2	*get_redir_lst(t_token *token)
{
	t_command	*cmd;

	if (token->type && token->type != TOKEN_COMMAND)
		return (NULL);
	cmd = (t_command *)token->data;
	if (cmd->redirects)
		return (cmd->redirects);
	return (NULL);
}

//[FUNCTION]____________________________

static int	fill_heredocs(t_list2 *rdr_lst, t_minishell *ms)
{
	t_list2		*tmp;
	t_redirect	*rdr;

	tmp = rdr_lst;
	if (!rdr_lst)
		return (1);
	while (tmp)
	{
		rdr = (t_redirect *)tmp->content;
		if (rdr->type == REDIRECT_HEREDOC)
			create_heredoc(rdr, ms);
		tmp = tmp->next;
	}
	return (0);
}

int	handle_heredocs(t_list2 *tokens, t_minishell *ms)
{
	t_list2		*tmp;
	t_list2		*rdr_lst;

	ms->tokens = tokens;
	tmp = tokens;
	while (tmp)
	{
		rdr_lst = get_redir_lst(tmp->content);
		fill_heredocs(rdr_lst, ms);
		tmp = tmp->next;
	}
	ms->tokens = NULL;
	return (0);
}
