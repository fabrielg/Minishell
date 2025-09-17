#include "exec.h"

/**
 * @brief Executes the pwd builtin by printing the current directory.
 * @return 0 on success, 1 if PWD is unset
 */
int	cmd_pwd(char **args, t_mst **env)
{
	t_mst	*node;

	(void)args;
	node = mst_get_node(*env, "PWD");
	if (!node || !node->dic.value)
		return (EXIT_FAILURE);
	write(STDOUT_FILENO, node->dic.value, ft_strlen(node->dic.value));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
