#include "ast.h"

/**
 * @brief Marks a command token as seen and advances the token pointer.
 */
static void	read_command(bool *seen_ptr, t_list2 **tokens)
{
	*seen_ptr = true;
	*tokens = (*tokens)->next;
}

/**
 * @brief Skips over a subshell, updating seen status and advancing tokens.
 */
static void	read_subshell(bool *seen_ptr, t_list2 **tokens)
{
	int		depth;
	t_token	*tok;

	depth = 0;
	*seen_ptr = true;
	while (*tokens)
	{
		tok = (t_token *)(*tokens)->content;
		if (tok->type == TOKEN_SUBSHELL)
		{
			if (ft_strcmp(tok->data, "(") == 0)
				depth++;
			else if (ft_strcmp(tok->data, ")") == 0)
			{
				depth--;
				if (depth == 0)
				{
					*tokens = (*tokens)->next;
					break ;
				}
			}
		}
		*tokens = (*tokens)->next;
	}
}

/**
 * @brief Handles a pipeline token, updating count if a command was seen.
 */
static void	read_pipeline(bool *seen_ptr, size_t *count_ptr, t_list2 **tokens)
{
	if (*seen_ptr)
		(*count_ptr)++;
	*seen_ptr = false;
	*tokens = (*tokens)->next;
}

/**
 * @brief Counts the number of commands or subshells in a pipeline.
 * @return Number of arguments in the pipeline
 */
size_t	ast_count_args_pipeline(t_list2 *tokens)
{
	size_t	count;
	t_token	*tok;
	bool	seen_command;

	count = 0;
	seen_command = false;
	while (tokens)
	{
		tok = (t_token *)tokens->content;
		if (tok->type == TOKEN_COMMAND)
			read_command(&seen_command, &tokens);
		else if (tok->type == TOKEN_SUBSHELL && ft_strcmp(tok->data, "(") == 0)
			read_subshell(&seen_command, &tokens);
		else if (tok->type == TOKEN_PIPELINE)
			read_pipeline(&seen_command, &count, &tokens);
		else
			break ;
	}
	if (seen_command)
		count++;
	return (count);
}
