#include "exec.h"

int	cmd_pwd(char **args, t_mst **env)
{
	t_mst	*node;

	node = mst_get_node(*env, "PWD");
	if (!node || !node->dic.value)
		return (EXIT_FAILURE);
	write(STDOUT_FILENO, node->dic.value, ft_strlen(node->dic.value));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
