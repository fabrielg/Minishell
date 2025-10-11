#include "lexer.h"

/**
 * @brief Writes a syntax error message to stderr.
 * @return err_code
 */
int	print_stx_error(int err_code, char *err_msg, int len)
{
	write(2, STX_ERROR_MSG, ft_strlen(STX_ERROR_MSG));
	write(2, err_msg, len);
	write(2, "'\n", 2);
	return (err_code);
}

/**
 * @brief Lexically checks a command line for syntax errors.
 * @param cmd_line Input command line string
 * @return LXG_ERROR (2) if error, 1 if valid
 */
int	lex_line(char *cmd_line)
{
	int				i;
	int				par_count;
	unsigned char	byte;

	if (!cmd_line || cmd_line[0] == '\0')
		return (STX_ERROR);
	i = -1;
	byte = 0b0000;
	par_count = 0;
	while (cmd_line[++i])
	{
		if (cmd_line[i] != ' ')
		{
			toggle_quotes(cmd_line[i], &byte);
			if (!check_operators(cmd_line, &i, &byte)
				|| !check_parenthesis(cmd_line[i], &par_count, byte))
				return (STX_ERROR);
		}
	}
	return (validate_stx(par_count, byte));
}
