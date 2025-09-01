
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

void check_quotes(char *cmd_line, int *i, char	*byte)
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
	unsigned char	byte;

	i = -1;
	byte = 0b0;
	while (cmd_line[++i])
	{
		check_quotes(cmd_line, &i, &byte);
		printf("%c\n", cmd_line[i]);
	}
	ft_putbits(byte);
	if (byte)
		return (printf("ERROR\n"), LXG_ERROR);
	return (printf("OK\n"), 1);
}	
