#include "exec.h"

int	cmd_unset(char **args, t_mst **env)
{
	int	i;

	i = 0;
	if (!args[1])
		return (0);
	while (args[++i])
		mst_delete(env, args[i]);
	printf("\n\nunset_cmd\n\n");
	return (SUCCESS);
}
