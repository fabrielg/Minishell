/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shebang_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:11:05 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:11:29 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include <sys/stat.h>
#include <errno.h>

#define BASH_DIR "/bin/bash"

/**
 * @brief Executes a script without a shebang using /bin/bash and handles errors.
 * @return Exit code of the attempted execution
 */
t_uint8	no_shebang_case(char *arg, char **env, t_uint8 *code, t_minishell *ms)
{
	char	*tab[3];

	tab[0] = BASH_DIR;
	tab[1] = arg;
	tab[2] = NULL;
	execve(BASH_DIR, tab, env);
	free(env);
	pipe_clear(ms->pipes, ms->child_pids);
	if (errno == EACCES)
		return (cmd_err(code, arg, NO_PERM_MSG, PERM_ERR));
	return (cmd_err(code, arg, NOT_FOUND_MSG, NOT_FOUND_ERR));
}
