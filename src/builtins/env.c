/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:08:27 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:08:27 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Executes the env builtin, displaying environment variables.
 * @return 0
 */
t_uint8	cmd_env(char **args, t_mst **env)
{
	if (args[1])
		return (NOT_FOUND_ERR);
	mst_display(*env);
	return (0);
}
