#include "tokens.h"
#include "lexer.h"
#include "parser.h"

t_list2	*parser(char *command_line, t_mst *env, int exit_code)
{
	char	**contents;
	t_list2	*tokens;

	if (lex_line(command_line) == 2)
		return (NULL);
	contents = smart_split(command_line);
	if (!contents)
		return (NULL);
	tokens = tokenize(contents);
	ft_free_map((void **) contents, -1);
	if (!tokens)
		return (NULL);
	tokens = group_commands(tokens);
	if (!tokens)
		return (NULL);
	expander(tokens, env, exit_code);
	if (!tokens)
		return (NULL);
	return (tokens);
}
