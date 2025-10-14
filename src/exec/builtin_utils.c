/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:11:59 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:11:59 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

/**
 * @brief Handles exit status for exit builtin.
 * @return Exit code on success, -1 on error
 */
int	handle_exit(t_command *cmd, t_minishell *ms, t_uint8 *exit_code)
{
	if (cmd->argc == 1)
		*exit_code = ms->last_exit_code;
	if ((cmd->argc >= 2 && *exit_code != 1) || cmd->argc == 1)
		return (*exit_code);
	return (-1);
}

/**
 * @brief Matches command name to builtin function.
 * @note set flag to 1 if builtin is exit
 * @return Function pointer to builtin, NULL if not found
 */
t_builtin	get_builtin(char *name, t_uint8 *flag)
{
	if (!ft_strcmp(name, "echo"))
		return (cmd_echo);
	else if (!ft_strcmp(name, "cd"))
		return (cmd_cd);
	else if (!ft_strcmp(name, "pwd"))
		return (cmd_pwd);
	else if (!ft_strcmp(name, "export"))
		return (cmd_export);
	else if (!ft_strcmp(name, "unset"))
		return (cmd_unset);
	else if (!ft_strcmp(name, "env"))
		return (cmd_env);
	else if (!ft_strcmp(name, "exit"))
	{
		if (flag)
			*flag = F_EXIT;
		return (cmd_exit);
	}
	return (NULL);
}
