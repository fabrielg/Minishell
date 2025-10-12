#include "minishell.h"
#include "tokens.h"
#include "lexer.h"
#include "parser.h"
#include "sig.h"

static t_list2	*set_pr_exit_code(int value, t_minishell *ms)
{
	ms->shell_exit_code = value;
	return (NULL);
}

/**
 * @brief Parse the input line into a list of commands and tokens.
 * @return Linked list of tokens or NULL on error.
 */
t_list2	*parser(t_minishell *ms)
{
	char	**contents;
	t_list2	*tokens;
	char	*line_trim;

	line_trim = ft_strtrim(ms->input_line, " \a\b\t\n\v\f\r");
	if (!line_trim)
		return (set_pr_exit_code(1, ms));
	free(ms->input_line);
	ms->input_line = line_trim;
	if (lex_line(ms->input_line) == 2)
		return (set_pr_exit_code(1, ms));
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
