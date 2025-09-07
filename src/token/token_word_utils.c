#include "tokens.h"

t_token	*token_create_word(t_word *word)
{
	t_token	*token;

	if (!word)
		return (NULL);
	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = TOKEN_WORD;
	token->data = word;
	return (token);
}

t_word	*token_parse_word(char *content)
{
	t_word	*word;

	word = (t_word *) malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	word->expandable = false;
	word->quoted = false;
	if (ft_strchrset(content, "'\""))
		word->quoted = true;
	word->text = ft_strdup(content);
	if (!word->text)
		return (free(word), NULL);
	return (word);
}

void	token_destroy_word(t_word *word)
{
	if (!word)
		return ;
	free(word->text);
	free(word);
}