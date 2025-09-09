#include "tokens.h"

t_word	*parse_word(char *content)
{
	t_word	*word;

	word = (t_word *) malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	word->text = ft_strdup(content);
	if (!word->text)
		return (free(word), NULL);
	word->expandable = false;
	if (word->text && word->text[0] != '\'' && ft_strchr(content, '$'))
		word->expandable = true;
	return (word);
}

t_token	*token_new_word(const char *s)
{
	t_token	*token;
	t_word	*w;

	w = parse_word((char *)s);
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
	t_word	*word;

	word = (t_word *) data;
	if (!word)
		return ;
	if (word->text)
		free(word->text);
	free(word);
}

t_word	*get_word(void *data)
{
	t_word	*w;

	w = (t_word *) data;
	return (w);
}

void	token_display_word(t_word *word)
{
	if (!word)
		return ;
	printf("TOKEN_WORD=[%s]", word->text);
	if (word->expandable)
		printf(" (expandable)");
}
