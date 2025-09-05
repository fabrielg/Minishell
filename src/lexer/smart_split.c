#include "lexer.h"

static int	count_words(const char *line)
{
	unsigned char	byte;
	int				count;
	int				i;
	bool			in_word;

	count = 0;
	byte = 0;
	i = 0;
	in_word = false;
	while (line && line[i])
	{
		toggle_quotes(line[i], &byte);
		if (!(byte & IN_QUOTES) && (line[i] == ' ' || line[i] == '\t'))
		{
			if (in_word)
				count++;
			in_word = false;
		}
		else
			in_word = true;
		i++;
	}
	if (in_word)
		count++;
	return (count);
}

static char	*extract_word(const char *line, int *i)
{
	unsigned char	byte;
	int				start;
	int				j;

	if (!line)
		return (NULL);
	byte = 0;
	j = *i;
	start = j;
	while (line[j])
	{
		toggle_quotes(line[j], &byte);
		if (!(byte & IN_QUOTES) && (line[j] == ' ' || line[j] == '\t'))
			break ;
		j++;
	}
	*i = j;
	return (ft_strndup(line + start, j - start));
}

char	**smart_split(const char *line)
{
	char	**res;
	int		words;
	int		i;
	int		x;

	words = count_words(line);
	res = calloc(words + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	x = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (!line[i])
			break ;
		res[x] = extract_word(line, &i);
		if (!res[x])
			return (ft_free_map((void **) res, x), NULL);
		x++;
	}
	return (res);
}
