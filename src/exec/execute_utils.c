#include "exec.h"
#include "minishell.h"
#include <sys/stat.h>
#include <errno.h>

#define BASH_DIR "/bin/bash"

static t_uint8	no_shebang_case(t_uint8 *exit_code, char *arg, char **env_cpy)
{
	char	*tab[3];

	tab[0] = BASH_DIR;
	tab[1] = arg;
	tab[2] = NULL;

	execve(BASH_DIR, tab, env_cpy);
	free(env_cpy);
	if (errno == EACCES)
		return (cmd_err(exit_code, arg, NO_PERM_MSG, PERM_ERR));
	return (cmd_err(exit_code, arg, NOT_FOUND_MSG, NOT_FOUND_ERR));
}

/**
 * @brief Checks if the command is a builtin and executes it.
 * @note Set exit_code to the builtin return value
 * @return 1 if builtin executed, 0 otherwise
 */
t_uint8	is_builtin(char **args, t_mst **env, t_uint8 *exit_code)
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

/**
 * @brief Executes command if path is absolute or relative.
 * @note Set exit_code to the adapted error (0, 1, 126 or 127)
 * @return 1 if executed or error handled, 0 otherwise
 */
t_uint8	is_abs_rltv_path(char **args, t_mst *env, t_uint8 *exit_code)
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
		return (cmd_err(exit_code, NULL, NULL, 1));
	execve(args[0], args, env_cpy);
	if (errno == ENOEXEC)
		return (no_shebang_case(exit_code ,args[0], env_cpy));
	free(env_cpy);
	if (errno == EACCES)
		return (cmd_err(exit_code, args[0], NO_PERM_MSG, PERM_ERR));
	return (cmd_err(exit_code, args[0], NOT_FOUND_MSG, NOT_FOUND_ERR));
}

/**
 * @brief Executes command if found in PATH variable.
 * @note Set exit_code to the adapted error (0, 1, 126 or 127)
 * @return 1 if executed or error handled, 0 otherwise
 */
t_uint8	is_in_path(char **args, t_mst *m_path, t_mst *env, t_uint8 *exit_code)
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
		return (free(path), cmd_err(exit_code, NULL, NULL, 1));
	execve(path, args, env_cpy);
	free(path);
	free(env_cpy);
	if (errno == EACCES)
		return (cmd_err(exit_code, args[0], NO_PERM_MSG, PERM_ERR));
	return (cmd_err(exit_code, args[0], NOT_FOUND_MSG, NOT_FOUND_ERR));
}
