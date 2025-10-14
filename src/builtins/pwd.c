/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:08:34 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:08:34 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Executes the pwd builtin by printing the current directory.
 * @return 0 on success, 1 if PWD is unset
 */
t_uint8	cmd_pwd(char **args, t_mst **env)
{
	char	cwd[PATH_MAX_LEN];

	(void)env;
	(void)args;
	if (!getcwd(cwd, PATH_MAX_LEN))
		return (1);
	write(STDOUT_FILENO, cwd, ft_strlen(cwd));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
