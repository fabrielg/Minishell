#include "exec.h"

int	cmd_export(char **args, t_mst **env)
{
	int		i;
	t_dic	dic;
	t_mst	*node;

	i = 0;
	if (!args[1])
		return (bst_display(*env), 0);
	while (args[++i])
	{
		dic = split_env_var(args[i]);
		node = new_mst(dic);
		if (mst_insertion(env, node) == 1)
			return (EXIT_FAILURE);
	}
	return (0);
}
