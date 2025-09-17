#include "exec.h"

/**
 * @brief Executes the unset builtin, removing variables from environment.
 * @return 0
 */
int	cmd_unset(char **args, t_mst **env)
{
	int	i;

	i = 0;
	if (!args[1])
		return (0);
	while (args[++i])
		mst_delete(env, args[i]);
	return (0);
}
