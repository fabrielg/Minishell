/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:51:08 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/03/10 16:16:57 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int		words;
	int		is_word;

	words = 0;
	is_word = 0;
	while (*s)
	{
		if (*s != c && !is_word)
		{
			words++;
			is_word = 1;
		}
		else if (*s == c)
			is_word = 0;
		s++;
	}
	return (words);
}

static int	word_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

void	free_split(char **split)
{
	size_t	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	**ft_split(char const *s, char c)
{
	char		**split;
	int			words;
	int			len;
	int			i;

	words = count_words(s, c);
	split = malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (0);
	i = -1;
	while (++i < words)
	{
		while (*s == c)
			s++;
		len = word_len(s, c);
		split[i] = ft_substr(s, 0, len);
		if (!split[i])
		{
			free_split(split);
			return (0);
		}
		s += len;
	}
	split[words] = NULL;
	return (split);
}
