#include "tokens.h"
#include "wildcard.h"

static int	glob_one_redir(t_redirect *redir)
{
	int		count;
	char	**expanded;

	expanded = glob_token(redir->file, &count);
	if (!expanded)
		return (0);
	if (count > 1)
	{
		ft_free_map((void **)expanded, -1);
		return (-1);
	}
	free(redir->file);
	redir->file = ft_strdup(expanded[0]);
	ft_free_map((void **)expanded, -1);
	if (!redir->file)
		return (0);
	return (1);
}

int	glob_redirects_list(t_list2 *redirects)
{
	t_list2		*curr;
	t_redirect	*redir;

	curr = redirects;
	while (curr)
	{
		redir = (t_redirect *) curr->content;
		if (glob_one_redir(redir) == -1)
		{
			redir->type = REDIRECT_AMBIGUOUS;
			return (-1);
		}
		curr = curr->next;
	}
	return (1);
}
