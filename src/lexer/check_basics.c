
#include "libft.h"

#define SNG_QUOTED  0b0001
#define DBL_QUOTED  0b0010
#define CMD_READ    0b0100
#define OP_READ     0b1000
#define IN_QUOTES   0b0011
#define LXG_ERROR   120

/**
 * @brief Print the given bits (char size).
 */
void	ft_putbits(char bits)
{
	int				i;
	unsigned char	mask;

	i = -1;
	mask = 0b10000000;
	while (++i < (int)(sizeof(unsigned char) * 8))
	{
		ft_putchar_fd((!!(mask & bits)) + '0', 1);
		mask >>= 1;
	}
	write(1, "\n", 1);
}

int	is_op_valid(char *cmd_line, int *i)
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

//
int	check_op(char *cmd_line, int *i, unsigned char	*byte)
{
	if ((*byte & IN_QUOTES))
		return (1);
	if (cmd_line[*i] == '|' || cmd_line[*i] == '&')
	{
		if (!(*byte & CMD_READ)) //SI rien avant
			return (printf("operator error\n"), 0);
		if (!is_op_valid(cmd_line, i)) //check si set valide (&& ou || ou |)
			return (printf("op invalid\n"), 0);
		*byte &= 0b0011; //retour à aucun char lu
		*byte |= OP_READ;
	}
	else if (cmd_line[*i] == '>' || cmd_line[*i] == '<')
	{
		if ((*byte & OP_READ))
			return (printf("redir error\n"), 0);
		if (!is_op_valid(cmd_line, i)) //check si set valide (>> ou > ou << ou <)
			return (printf("op invalid\n"), 0);
		*byte &= 0b0011; //retour à aucun char lu
		*byte |= OP_READ;
	}
	else
	{
		*byte = 0b0100;    //sinon char lu
	}
	return (1);
}

int	check_parenthesis(char c, int *par_count, unsigned char	byte)
{
	if ((byte & IN_QUOTES))
		return (1);
	if (c == '(')
		(*par_count)++;
	else if (c == ')')
	{
		if (!(*par_count))
			return (0);
		(*par_count)--;
	}
	return (1);
}

void set_quotes(char c, int *i, unsigned char	*byte)
{
	if (c == '"' && !(*byte & SNG_QUOTED))
		*byte ^= DBL_QUOTED;
	else if (c == '\'' && !(*byte & DBL_QUOTED))
		*byte ^= SNG_QUOTED;
}  

int	check_basics(char *cmd_line)
{
	int				i;
	int				par_count;
	unsigned char	byte;

	i = -1;
	byte = 0b0000;
	par_count = 0;
	while (cmd_line[++i])
	{
		if (cmd_line[i] != ' ')
		{
			set_quotes(cmd_line[i], &i, &byte);
			if (!check_parenthesis(cmd_line[i], &par_count, byte)
				|| !check_op(cmd_line, &i, &byte))
				return (printf("ERROR SYNTAX\n"), LXG_ERROR);
		}
	}
	ft_putbits(byte);
	// printf("par_count : %i\n", par_count);
	if (!(byte & 0b0100) || byte & IN_QUOTES || par_count)
		return (printf("ERROR DE FOU\n"), LXG_ERROR);
	return (printf("OK\n"), 1);
}
