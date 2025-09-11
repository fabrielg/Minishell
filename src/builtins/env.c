#include "exec.h"

int	cmd_env(char **args, t_mst **env)
{
	if (args[1])
		return (0);
	mst_display(*env);
	return (0);
}
