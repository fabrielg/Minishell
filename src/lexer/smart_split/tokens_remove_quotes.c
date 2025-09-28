#include "libft.h"
#include "lexer.h"
#include "smart_split.h"

static char	*remove_paired_quotes(const char *str)
{
	char			*res;
	unsigned char	quote;
	int				len;
	int				i;
	int				j;

	len = ft_strlen(str);
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	quote = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		toggle_quotes(str[i], &quote);
		if (str[i] == '\'' && quote & DBL_QUOTED)
			res[j++] = str[i];
		else if (str[i] == '"' && quote & SNG_QUOTED)
			res[j++] = str[i];
		else if (!ft_strchr("'\"", str[i]))
			res[j++] = str[i];
		i++;
	}
	return (res);
}

void	token_unquote(char **str_ptr)
{
	char	*clean;

	clean = remove_paired_quotes(*str_ptr);
	free(*str_ptr);
	*str_ptr = clean;
}

void	tokens_remove_quotes(char **tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		token_unquote(&tokens[i]);
		i++;
	}
}
