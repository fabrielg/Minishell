#include "libft.h"

int	exec_error(char *cmd, char *msg, int exit_code)
{
	if (cmd)
	{
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": ", 2);
	}
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	return (exit_code);
}

// int	print_cmd_error(char *cmd, char *arg, char *msg, int exit_code)
// {
// 	if (cmd)
// 	{
// 		write(STDERR_FILENO, cmd, ft_strlen(cmd));
// 		write(STDERR_FILENO, ": ", 2);
// 	}
// 	if (arg)
// 	{
// 		write(STDERR_FILENO, cmd, ft_strlen(cmd));
// 		write(STDERR_FILENO, ": ", 2);
// 	}
// 	if (msg)
// 		write(STDERR_FILENO, msg, ft_strlen(msg));
// 	return (exit_code);
// }
