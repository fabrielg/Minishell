#include "tokens.h"
#include "lexer.h"
#include "parser.h"

t_list2	*parser(t_minishell *ms)
{
	char	**contents;
	t_list2	*tokens;

	if (lex_line(ms->input_line) == 2)
		return (NULL);
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
		return (NULL);
	expander(tokens, ms->exports, ms->last_exit_code);
	if (!tokens)
		return (NULL);
	glob_commands(tokens);
	return (tokens);
}
