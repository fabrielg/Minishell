/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:07:55 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:07:57 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/**
 * @brief Parses commands from a token list into an array of AST nodes.
 */
static void	parse_commands(t_list2 **tokens, t_ast **cmds)
{
	size_t	i;
	t_token	*tok;

	i = 0;
	while (*tokens)
	{
		tok = (t_token *)(*tokens)->content;
		if (tok->type == TOKEN_COMMAND
			|| (tok->type == TOKEN_SUBSHELL && ft_strcmp(tok->data, "(") == 0))
		{
			cmds[i++] = parse_simple_command_or_subshell(tokens);
			continue ;
		}
		else if (tok->type == TOKEN_PIPELINE)
			*tokens = (*tokens)->next;
		else
			break ;
	}
	cmds[i] = NULL;
}

/**
 * @brief Parses a pipeline of commands from a token list.
 * @return AST node representing the pipeline, or NULL on failure/empty
 */
t_ast	*parse_pipeline(t_list2 **tokens)
{
	t_ast	**cmds;
	size_t	count;

	count = ast_count_args_pipeline(*tokens);
	if (count == 0)
		return (NULL);
	else if (count == 1)
		return (parse_simple_command_or_subshell(tokens));
	cmds = ft_calloc(count + 1, sizeof(t_ast *));
	if (!cmds)
		return (NULL);
	parse_commands(tokens, cmds);
	return (ast_new_pipeline(cmds, count));
}
