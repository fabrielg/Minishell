/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 22:15:10 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/09/15 00:24:17 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	t_mst		*env;
	t_list2		*cmds;
	t_command	*cmd;
	t_token		*token;


	if (argc != 2)
		return (0);

	char *arr[] = {"25", "20", "22", "10", "12", "15", "05", "01",
		"08", "36", "30", "28", "40", "38", "48", "45", "50", NULL};
	// char *arr[] = {NULL};
	t_mst		*nb_mst;

	nb_mst = mst_alloc_env(arr);
	debug_node(mst_get_node(nb_mst, argv[1]));
	mst_delete(&nb_mst, argv[1]);
	mst_display(nb_mst);
	bst_display(nb_mst);

	// env = mst_alloc_env(envp);
	// env_deletion(&env, argv[1]);
	// mst_display(env);
	// printf("[%s]\n", env_cpy[0]);

	// cmds = parser(argv[1]);
	// token = (t_token *)cmds->content;
	// cmd = get_command(token->data);

	// // token_display_command(cmd);
	// exec(cmd, &env);
	mst_clear(&nb_mst);
	// ft_lstclear2(&cmds, token_destroy);
	return (0);
}
