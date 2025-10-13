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
	if (arg[i] != '-' || len < 2)
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
	while (args[i] && get_flag(args[i], ft_strlen(args[i]), &i))
		flag = N_FLAG;
	if (args[i])
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
	while (args[i] && args[i + 1])
	{
		if (args[i][0])
			write(STDOUT_FILENO, " ", 1);
		i++;
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
	}
	if (!(flag & N_FLAG))
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
