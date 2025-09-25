#include "lexer.h"
#include <string.h>

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
