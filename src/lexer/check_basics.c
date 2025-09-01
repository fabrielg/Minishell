
#include "libft.h"

#define SNG_QUOTED 0b01
#define DBL_QUOTED 0b10
#define LXG_ERROR 120

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

int	check_parenthesis(char c, int *par_count, unsigned char	byte)
{
	if (byte)
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

void set_quotes(char *cmd_line, int *i, unsigned char	*byte)
{
	if (cmd_line[*i] == '\\' && !(*byte & SNG_QUOTED))
	{
		if (cmd_line[*i + 1])
			(*i)++;
	}
	else if (cmd_line[*i] == '"' && !(*byte & SNG_QUOTED))
		*byte ^= DBL_QUOTED;
	else if (cmd_line[*i] == '\'' && !(*byte & DBL_QUOTED))
		*byte ^= SNG_QUOTED;
}

int	check_basics(char *cmd_line)
{
	int				i;
	int				par_count;
	unsigned char	byte;

	i = -1;
	byte = 0b0;
	par_count = 0;
	while (cmd_line[++i])
	{
		set_quotes(cmd_line, &i, &byte);
		if (!check_parenthesis(cmd_line[i], &par_count, byte))
			return (printf("ERROR\n"), LXG_ERROR);
		printf("%c\n", cmd_line[i]);
	}
	ft_putbits(byte);
	printf("par_count : %i\n", par_count);
	if (byte || par_count)
		return (printf("ERROR\n"), LXG_ERROR);
	return (printf("OK\n"), 1);
}
