/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_remove_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:17:57 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:17:57 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "smart_split.h"

/**
 * @brief Removes paired single/double quotes from a string.
 * @return Newly allocated string without paired quotes, NULL on error
 */
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

/**
 * @brief Removes paired quotes from a single token in place.
 */
void	token_unquote(char **str_ptr)
{
	char	*clean;

	clean = remove_paired_quotes(*str_ptr);
	free(*str_ptr);
	*str_ptr = clean;
}

/**
 * @brief Removes paired quotes from an array of tokens.
 */
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
