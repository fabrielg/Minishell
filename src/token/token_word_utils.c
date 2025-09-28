#include "tokens.h"

void	token_destroy_word(void *data)
{
	char	*word;

	word = (char *) data;
	if (word)
		free(word);
}

bool	is_expandable_word(char *word)
{
	int		i;
	char	quote;

	if (!word)
		return (false);
	i = 0;
	quote = 0;
	while (word[i])
	{
		if (!quote && (word[i] == '\'' || word[i] == '"'))
			quote = word[i];
		else if (quote && word[i] == quote)
			quote = 0;
		else if (word[i] == '$' && quote != '\'')
			return (true);
		i++;
	}
	return (false);
}

void	token_display_word(char *word)
{
	if (!word)
		return ;
	printf("TOKEN_WORD=[%s]", word);
	if (is_expandable_word(word))
		printf(" (expandable)");
}
