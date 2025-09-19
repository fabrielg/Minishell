#include "exec.h"

/**
 * @brief Executes the pwd builtin by printing the current directory.
 * @return 0 on success, 1 if PWD is unset
 */
int	cmd_pwd(char **args, t_mst **env)
{
	t_mst	*node;
	char	cwd[PATH_MAX_LEN];

	(void)args;
	if (!getcwd(cwd, PATH_MAX_LEN))
		return (1);
	write(STDOUT_FILENO, cwd, ft_strlen(cwd));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
