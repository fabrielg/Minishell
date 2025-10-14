/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_redirs_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:21:56 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:21:57 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "wildcard.h"

/**
 * @brief Expand wildcards in a single redirect filename.
 * @return 1 if expanded successfully, 0 on error, -1 if ambiguous.
 */
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

/**
 * @brief Expand wildcards for all redirects in a list.
 * @return 1 if all successful, -1 if any ambiguous.
 */
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
