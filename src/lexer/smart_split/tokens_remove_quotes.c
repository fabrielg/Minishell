#include "libft.h"
#include "lexer.h"
#include "smart_split.h"

char	*remove_paired_quotes(const char *str)
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

void	tokens_remove_quotes(t_split_ctx ctx)
{
	char	*clean;
	int		i;

	i = 0;
	while (i < ctx.count)
	{
		clean = remove_paired_quotes(ctx.tokens[i]);
		free(ctx.tokens[i]);
		ctx.tokens[i] = clean;
		i++;
	}
}
