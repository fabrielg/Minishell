#include "tokens.h"
#include "lexer.h"
#include "parser.h"
#include "expander.h"

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
		return (NULL);
	free(ms->input_line);
	ms->input_line = line_trim;
	if (!line_trim[0])
		return (NULL);
	if (lex_line(ms->input_line) == 2)
		return (set_err(&ms->last_exit_code, 2), NULL);
	contents = smart_split(ms->input_line);
	if (!contents)
		return (NULL);
	tokens = tokenize(contents);
	ft_free_map((void **) contents, -1);
	if (!tokens)
		return (NULL);
	tokens = group_commands(tokens);
	if (!tokens)
		return (NULL);
	if (handle_heredocs(tokens, ms))
		return (ft_lstclear2(&tokens, token_destroy), NULL);
	return (tokens);
}
