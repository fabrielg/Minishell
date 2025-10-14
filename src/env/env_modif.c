/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_modif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:09:15 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:09:16 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"

/**
 * @brief Modifies the value of an existing MST node by key.
 * @param env       Pointer to MST root
 * @param key       Key of the node to modify
 * @param new_value New value to assign
 * @return 0 on success, 1 on failure
 */
int	mst_modif_value(t_mst **env, char *key, char *new_value)
{
	t_mst	*new;
	char	*temp;

	if (!mst_get_node(*env, key))
		return (1);
	temp = ft_strjoin3(key, "=", new_value);
	if (!temp)
		return (1);
	new = new_mst(split_env_var(temp));
	if (mst_insertion(env, new))
		return (1);
	free(temp);
	return (0);
}
