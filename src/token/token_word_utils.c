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
	if (!word)
		return (false);
	if (word[0] != '\'' && ft_strchr(word, '$'))
		return (true);
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
