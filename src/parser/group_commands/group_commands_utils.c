/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_commands_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:21:27 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:21:28 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "parser.h"

/**
 * @brief Adds the current command to the result list and resets it.
 */
void	flush_command(t_list2 **result, t_command **current)
{
	if (*current)
	{
		ft_lstadd_back2(result, ft_lstnew2(token_create_command(*current)));
		*current = NULL;
	}
}
