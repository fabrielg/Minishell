/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:12:11 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:13:29 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include <sys/stat.h>
#include <errno.h>
#include <sys/wait.h>
#include "sig.h"

/**
 * @brief Converts a process wait status to a shell exit code.
 * @return Exit code corresponding to process termination
 */
int	cmd_exit_status(int status, t_minishell *ms)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT && !ms->in_pipe)
		{
			write(STDERR_FILENO, "\n", 1);
			ms->signal_received = true;
		}
		if (WTERMSIG(status) == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n", 20);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

/**
 * @brief Checks if the command is a builtin and executes it.
 * @note Set exit_code to the builtin return value
 * @return 1 if builtin executed, 0 otherwise
 */
t_uint8	is_builtin(char **args, t_mst **env, t_uint8 *exit_code)
{
	t_builtin	f;

	f = NULL;
	if (args && args[0])
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
t_uint8	is_abs_rltv_path(char **args, t_minishell *ms, t_uint8 *exit_code)
{
	struct stat		st;
	char			**env_cpy;

	if (!ft_strchr(args[0], '/'))
		return (0);
	if (stat(args[0], &st) == -1)
		return (cmd_err(exit_code, args[0], NO_PATH_MSG, NOT_FOUND_ERR));
	if (S_ISDIR(st.st_mode))
		return (cmd_err(exit_code, args[0], IS_DIR_MSG, PERM_ERR));
	if (args && args[0] && access(args[0], X_OK) == -1)
		return (cmd_err(exit_code, args[0], NO_PERM_MSG, PERM_ERR));
	env_cpy = env_newtab(ms->exports);
	if (!env_cpy)
		return (cmd_err(exit_code, NULL, NULL, 1));
	execve(args[0], args, env_cpy);
	if (errno == ENOEXEC)
		return (no_shebang_case(args[0], env_cpy, exit_code, ms));
	free(env_cpy);
	pipe_clear(ms->pipes, ms->child_pids);
	if (errno == EACCES)
		return (cmd_err(exit_code, args[0], NO_PERM_MSG, PERM_ERR));
	return (cmd_err(exit_code, args[0], NOT_FOUND_MSG, NOT_FOUND_ERR));
}

/**
 * @brief Executes command if found in PATH variable.
 * @note Set exit_code to the adapted error (0, 1, 126 or 127)
 * @return 1 if executed or error handled, 0 otherwise
 */
t_uint8	is_in_path(char **args, t_mst *m_path, t_minishell *ms, t_uint8 *code)
{
	char	**env_cpy;
	char	*path;

	if (args && !args[0])
	{
		*code = 0;
		return (1);
	}
	path = research_path(args[0], m_path->dic.value);
	if (!path)
		return (cmd_err(code, args[0], NOT_FOUND_MSG, NOT_FOUND_ERR));
	if (access(path, X_OK))
		return (free(path), cmd_err(code, args[0], NO_PERM_MSG, PERM_ERR));
	env_cpy = env_newtab(ms->exports);
	if (!env_cpy)
		return (free(path), cmd_err(code, NULL, NULL, 1));
	execve(path, args, env_cpy);
	free(path);
	free(env_cpy);
	pipe_clear(ms->pipes, ms->child_pids);
	if (errno == EACCES)
		return (cmd_err(code, args[0], NO_PERM_MSG, PERM_ERR));
	return (cmd_err(code, args[0], NOT_FOUND_MSG, NOT_FOUND_ERR));
}
