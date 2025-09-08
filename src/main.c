/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 22:15:10 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/09/08 22:16:26 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	t_mst	*mst;
	mst = mst_alloc_env(envp);
	mst_display(mst);
	printf("\n\n\n");
	bst_display(mst);
	printf("\n\n\n");
	t_mst	*node;
	node = mst_get_node(mst, "USER");
	if (node && node->dic)
		printf("%s=%s\n", node->dic->key, node->dic->value);
	else
		ft_putendl_fd("Not found !", 1);
	mst_clear(&mst);
	return (0);
}
