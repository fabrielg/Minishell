#include "exec.h"

#define N_FLAG 0b1

/**
 * @brief Parses echo option flag (-n).
 * @return N_FLAG if -n option, 0 otherwise
 */
static t_uint8	get_flag(char *arg, int len, int *id_out)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	while (++i < len)
		if (arg[i] != 'n')
			return (0);
	(*id_out)++;
	return (N_FLAG);
}

/**
 * @brief Executes the echo builtin, printing arguments with optional newline.
 * @return 0
 */
t_uint8	cmd_echo(char **args, t_mst **env)
{
	t_uint8			flag;
	int				i;

	i = 1;
	flag = 0b0;
	(void)env;
	if (args[1] && args[2])
		flag = get_flag(args[1], ft_strlen(args[1]), &i);
	if (args[1])
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
	while (args[1] && args[++i])
	{
		write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
	}
	if (!(flag & N_FLAG))
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
