#include "tokens.h"

t_token	*token_new_word(const char *s)
{
	t_token	*token;
	char	*w;

	w = ft_strdup(s);
	if (!w)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
	{
		token_destroy_word(w);
		return (NULL);
	}
	token->type = TOKEN_WORD;
	token->data = w;
	return (token);
}

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
