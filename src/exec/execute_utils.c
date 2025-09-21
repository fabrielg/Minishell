#include "exec.h"
#include <errno.h>
#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

int	is_builtin(char **args, t_mst **env, int *exit_code)
{
	t_builtin	f;

	f = get_builtin(args[0], NULL);
	if (f)
	{
		if (exit_code)
			*exit_code = f(args, env);
		return (1);
	}
	return (0);
}

static int	cmd_err(int *exit_code, char *arg, char *err_msg, int code)
{
	*exit_code = exec_error(arg, err_msg, code);
	return (1);
}

int	is_abs_rltv_path(char **args, t_mst *env, int *exit_code)
{
	struct stat		st;
	char			**env_cpy;

	if (!ft_strchr(args[0], '/'))
		return (0);
	if (stat(args[0], &st) == -1)
		return (cmd_err(exit_code, args[0], NO_PATH_MSG, NOT_FOUND_ERR));
	if (S_ISDIR(st.st_mode))
		return (cmd_err(exit_code, args[0], IS_DIR_MSG, PERM_ERR));
	if (access(args[0], X_OK) == -1)
		return (cmd_err(exit_code, args[0], NO_PERM_MSG, PERM_ERR));
	env_cpy = env_newtab(env);
	if (!env_cpy)
		return (cmd_err(exit_code, NULL, NULL, 0));
	execve(args[0], args, env_cpy);
	if (errno == EACCES)
		return (cmd_err(exit_code, args[0], NO_PERM_MSG, PERM_ERR));
	return (cmd_err(exit_code, args[0], NOT_FOUND_MSG, NOT_FOUND_ERR));
}

int	is_in_path(char **args, t_mst *m_path, t_mst *env, int *exit_code)
{
	char	**env_cpy;
	char	*path;

	path = research_path(args[0], m_path->dic.value);
	if (!path)
		return (cmd_err(exit_code, args[0], NOT_FOUND_MSG, NOT_FOUND_ERR));
	if (access(path, X_OK))
	{
		free(path);
		return (cmd_err(exit_code, args[0], NO_PERM_MSG, PERM_ERR));
	}
	env_cpy = env_newtab(env);
	if (!env_cpy)
		return (free(path), cmd_err(exit_code, NULL, NULL, 0));
	execve(path, args, env_cpy);
	free(path);
	free(env_cpy);
	if (errno == EACCES)
		return (cmd_err(exit_code, args[0], NO_PERM_MSG, PERM_ERR));
	return (cmd_err(exit_code, args[0], NOT_FOUND_MSG, NOT_FOUND_ERR));
}
