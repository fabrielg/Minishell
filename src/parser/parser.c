#include "tokens.h"
#include "lexer.h"

t_list2	*parser(char *command_line)
{
	char	**contents;
	t_list2	*tokens;

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
	return (tokens);
}
