#include "lexer.h"
#include <string.h>

/**
 * @brief Duplicate a substring [start, end).
 */
char	*substr(const char *s, int start, int end)
{
	char	*out;

	out = malloc((end - start + 1) * sizeof(char));
	if (!out)
		return (NULL);
	ft_memcpy(out, s + start, end - start);
	out[end - start] = 0;
	return (out);
}

/**
 * @brief Check if a char can start an operator.
 */
int	is_operator_char(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>'
		|| c == '(' || c == ')');
}

/**
 * @brief Check if substring starting at i is an operator and return its len.
 */
int	operator_len(const char *s, int i)
{
	if ((s[i] == '|' && s[i + 1] == '|')
		|| (s[i] == '&' && s[i + 1] == '&')
		|| (s[i] == '<' && s[i + 1] == '<')
		|| (s[i] == '>' && s[i + 1] == '>'))
		return (2);
	return (1);
}
