#include "exec.h"

/**
 * @brief Checks if a string represents a valid numeric value.
 * @return 1 if numeric, 0 otherwise
 */
static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Executes the exit builtin with optional status code.
 * @return Exit status
 */
t_uint8	cmd_exit(char **args, t_mst **env)
{
	t_uint8	status;

	(void)env;
	status = 0;
	if (!args[1])
		return (0);
	if (!is_numeric(args[1]))
	{
		write(STDERR_FILENO, "exit: numeric argument required\n", 32);
		return (2);
	}
	if (args[2])
	{
		write(STDERR_FILENO, "exit: too many arguments\n", 25);
		return (1);
	}
	status = (t_uint8)atoi(args[1]);
	return (status);
}
