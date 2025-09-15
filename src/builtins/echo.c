#include "exec.h"

#define N_FLAG 0b1

static unsigned char	get_flag(char *arg, int len, int *id_out)
{
	int				i;
	unsigned char	flag;

	flag = 0b0;
	i = 0;
	if (arg[i] != '-')
		return (0);
	while (++i < len)
		if (arg[i] != 'n')
			return (0);
	(*id_out)++;
	return (N_FLAG);
}

int	cmd_echo(char **args, t_mst **env)
{
	unsigned char	flag;
	int				i;

	i = 1;
	flag = 0b0;
	(void)env;
	if (!args[1])
		return (0);
	flag = get_flag(args[1], ft_strlen(args[1]), &i);
	write(STDOUT_FILENO, args[1], ft_strlen(args[1]));
	while (args[++i])
	{
		write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
	}
	if (!(flag & N_FLAG))
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
