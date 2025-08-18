/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 22:15:10 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/08/18 17:14:15 by alde-abr         ###   ########.fr       */
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
	print_tree(mst, 0);
	printf("\n\n\n");
	t_mst	*node;
	node = mst_search(mst, "USER");
	if (node && node->dic)
		printf("%s=%s\n", node->dic->key, node->dic->value);
	else
		ft_putendl_fd("Not found !", 1);
	mst_clear(&mst);
	return (0);
}
