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

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Duplicate a substring [start, end).
 */
static char *substr(const char *s, int start, int end)
{
    char *out = malloc(end - start + 1);
    if (!out) return NULL;
    memcpy(out, s + start, end - start);
    out[end - start] = '\0';
    return out;
}

/**
 * @brief Check if a char can start an operator.
 */
static int is_operator_char(char c)
{
    return (c == '|' || c == '&' || c == '<' || c == '>');
}

/**
 * @brief Check if substring starting at i is an operator and return its len.
 */
static int operator_len(const char *s, int i)
{
    if ((s[i] == '|' && s[i+1] == '|') ||
        (s[i] == '&' && s[i+1] == '&') ||
        (s[i] == '<' && s[i+1] == '<') ||
        (s[i] == '>' && s[i+1] == '>'))
        return 2;
    return 1;
}

char **smart_split_v2(const char *line)
{
    char **tokens = NULL;
    int capacity = 8, count = 0;
    int i = 0, start = -1;
    unsigned char state = 0;

    tokens = malloc(sizeof(char *) * capacity);
    if (!tokens) return NULL;

    while (line[i])
    {
        toggle_quotes(line[i], &state);

        if (!(state & IN_QUOTES))
        {
            if ((line[i] == ' ' || line[i] == '\t'))
            {
                if (start != -1) {
                    tokens[count++] = substr(line, start, i);
                    start = -1;
                }
            }
            else if (is_operator_char(line[i]))
            {
                if (start != -1) {
                    tokens[count++] = substr(line, start, i);
                    start = -1;
                }
                int oplen = operator_len(line, i);
                tokens[count++] = substr(line, i, i + oplen);
                i += oplen - 1;
            }
            else if (start == -1)
                start = i;
        }
        else
        {
            if (start == -1)
                start = i;
        }
        if (count >= capacity - 1)
        {
            capacity *= 2;
            tokens = realloc(tokens, sizeof(char *) * capacity);
        }
        i++;
    }
    if (start != -1)
        tokens[count++] = substr(line, start, i);

    tokens[count] = NULL;
    return tokens;
}
