#include "exec.h"

/**
 * @brief Executes the env builtin, displaying environment variables.
 * @return 0
 */
int	cmd_env(char **args, t_mst **env)
{
	if (args[1])
		return (NOT_FOUND_ERR);
	mst_display(*env);
	return (0);
}
