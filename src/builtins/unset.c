/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:08:36 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:08:37 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Executes the unset builtin, removing variables from environment.
 * @return 0
 */
t_uint8	cmd_unset(char **args, t_mst **env)
{
	int	i;

	i = 0;
	if (!args[1])
		return (0);
	while (args[++i])
		mst_delete(env, args[i]);
	return (0);
}
