#include "libft.h"

/**
 * @brief Prints an error message to STDERR and returns given exit code.
 * @param cmd       Command name (optional, may be NULL)
 * @param msg       Error message (optional, may be NULL)
 * @param exit_code Exit code to return
 * @return The given exit_code
 */
int	exec_err(char *cmd, char *msg, t_uint8 exit_code)
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

/**
 * @brief Prints an execution error and sets exit code.
 * @return  1
 */
t_uint8	cmd_err(t_uint8 *exit_code, char *arg, char *err_msg, int code)
{
	*exit_code = exec_err(arg, err_msg, code);
	return (1);
}
