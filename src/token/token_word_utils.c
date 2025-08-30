#include "tokens.h"

t_token	*token_create_word(char *text, bool quoted, bool expandable)
{
	t_token	*token;
	t_word	*word;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	word = (t_word *) malloc(sizeof(t_word));
	if (!word)
		return (free(token), NULL);
	word->text = ft_strdup(text);
	if (!word->text)
		return (free(token), free(word), NULL);
	word->quoted = quoted;
	word->expandable = expandable;
	token->type = TOKEN_WORD;
	token->data.word = word;
	return (token);
}

void	token_destroy_word(t_word *word)
{
	if (!word)
		return ;
	free(word->text);
	free(word);
}