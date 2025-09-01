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
	token->data.word = word;
	return (token);
}

t_token_data	token_parse_word(char *content)
{
	t_token_data	data;
	t_word			*word;

	data.word = NULL;
	word = (t_word *) malloc(sizeof(t_word));
	if (!word)
		return (data);
	word->expandable = false;
	word->quoted = false;
	if (ft_strchrset(content, "'\"") == 0)
		word->quoted = true;
	word->text = ft_strdup(content);
	if (!word->text)
		return (free(word), data);
	data.word = word;
	return (data);
}

void	token_destroy_word(t_word *word)
{
	if (!word)
		return ;
	free(word->text);
	free(word);
}