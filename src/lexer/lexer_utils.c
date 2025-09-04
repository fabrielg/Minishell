#include "lexer.h"

/**
 * @brief Checks if a sequence of operators is valid (|, &, >, <).
 * @return 1 if valid, 0 if invalid
 */
static int	validate_operator(char *cmd_line, int *i)
{
	char	c;
	int		j;
	int		count;

	count = 1;
	j = *i;
	c = cmd_line[*i];
	while (cmd_line[++j] == c && count < 3)
		count++;
	if ((c == '|' || c == '>' || c == '<') && count > 2)
		return (0);
	else if (c == '&' && count != 2)
		return (0);
	*i = j - 1;
	return (1);
}

/**
 * @brief Validates operators in the command line and updates byte state.
 * @return 1 if valid, 0 if invalid
 */
int	check_operators(char *cmd_line, int *i, unsigned char	*byte)
{
	if ((*byte & IN_QUOTES))
		return (1);
	if (cmd_line[*i] == '|' || cmd_line[*i] == '&')
	{
		if (!(*byte & WRD_READ) || !validate_operator(cmd_line, i))
			return (print_stx_error(0, &(cmd_line[*i]), 1));
		*byte = 0b0000;
	}
	else if (cmd_line[*i] == '>' || cmd_line[*i] == '<')
	{
		if ((*byte & RDR_READ) || !validate_operator(cmd_line, i))
			return (print_stx_error(0, &(cmd_line[*i]), 1));
		*byte = RDR_READ;
	}
	else
		*byte = WRD_READ;
	return (1);
}

/**
 * @brief Checks and updates parenthesis count.
 * @return 1 if valid, 0 if unmatched closing parenthesis
 */
int	check_parenthesis(char c, int *par_count, unsigned char byte)
{
	if ((byte & IN_QUOTES))
		return (1);
	if (c == '(')
		(*par_count)++;
	else if (c == ')')
	{
		if (!(*par_count))
			return (print_stx_error(0, &c, 1));
		(*par_count)--;
	}
	return (1);
}

/**
 * @brief Toggles quote state in the byte bitmask.
 */
void	toggle_quotes(char c, int *i, unsigned char *byte)
{
	if (c == '"' && !(*byte & SNG_QUOTED))
		*byte ^= DBL_QUOTED;
	else if (c == '\'' && !(*byte & DBL_QUOTED))
		*byte ^= SNG_QUOTED;
}

/**
 * @brief Checks the current syntax state for errors.
 * @return LXG_ERROR (2) if syntax error, 1 if valid
 */
int	validate_stx(int par_count, unsigned char byte)
{
	if (byte & DBL_QUOTED)
		return (print_stx_error(STX_ERROR, "\"", 1));
	else if (byte & SNG_QUOTED)
		return (print_stx_error(STX_ERROR, "'", 1));
	else if (!(byte & 0b0100))
		return (print_stx_error(STX_ERROR, "newline", 7));
	else if (par_count)
		return (print_stx_error(STX_ERROR, "(", 1));
	return (1);
}
