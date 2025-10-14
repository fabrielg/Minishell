/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:21:16 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:30:57 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include "lexer.h"
#include "parser.h"
#include "expander.h"
#include "sig.h"

static t_list2	*set_pr_exit_code(int value, t_minishell *ms)
{
	ms->shell_exit_code = value;
	return (NULL);
}

static int	trim_input_line(t_minishell *ms)
{
	char	*line_trim;

	line_trim = ft_strtrim(ms->input_line, " \a\b\t\n\v\f\r");
	if (!line_trim)
	{
		set_pr_exit_code(1, ms);
		return (0);
	}
	free(ms->input_line);
	ms->input_line = line_trim;
	if (!line_trim[0])
		return (0);
	return (1);
}

/**
 * @brief Parse the input line into a list of commands and tokens.
 * @return Linked list of tokens or NULL on error.
 */
t_list2	*parser(t_minishell *ms)
{
	char	**contents;
	t_list2	*tokens;

	if (!trim_input_line(ms))
		return (NULL);
	if (lex_line(ms->input_line) == 2)
		return (set_err(&ms->last_exit_code, 2), NULL);
	contents = smart_split(ms->input_line);
	if (!contents)
		return (set_pr_exit_code(1, ms));
	tokens = tokenize(contents);
	ft_free_map((void **) contents, -1);
	if (!tokens)
		return (set_pr_exit_code(1, ms));
	tokens = group_commands(tokens);
	if (!tokens)
		return (set_pr_exit_code(1, ms));
	if (handle_heredocs(tokens, ms))
	{
		ms->last_exit_code = 128 + SIGINT;
		return (ft_lstclear2(&tokens, token_destroy), NULL);
	}
	return (tokens);
}
