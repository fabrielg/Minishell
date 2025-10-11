#include "minishell.h"
#include "parser.h"
#include "expander.h"

/**
 * @brief Processes all heredoc redirections in a redirection list.
 * @return 0 on success, 1 on failure
 */
static int	fill_heredocs(t_list2 *rdr_lst, t_minishell *ms)
{
	t_list2		*tmp;
	t_redirect	*rdr;

	tmp = rdr_lst;
	if (!rdr_lst)
		return (0);
	while (tmp)
	{
		rdr = (t_redirect *)tmp->content;
		if (rdr->type == REDIRECT_HEREDOC)
		{
			if (create_heredoc(rdr, ms))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

/**
 * @brief Handles heredocs for all commands in the token list.
 * @return 0 on success, 1 if any heredoc creation fails
 */
int	handle_heredocs(t_list2 *tokens, t_minishell *ms)
{
	t_list2		*tmp;
	t_list2		*rdr_lst;

	ms->tokens = tokens;
	tmp = tokens;
	while (tmp)
	{
		rdr_lst = get_redir_lst(tmp->content);
		if (fill_heredocs(rdr_lst, ms))
			return (1);
		tmp = tmp->next;
	}
	ms->tokens = NULL;
	return (0);
}
