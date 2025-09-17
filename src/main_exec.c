/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 22:15:10 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/09/17 21:21:05 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	t_mst		*env;
	t_list2		*tokens;
	t_command	*cmd;
	t_token		*token;
	char		*line;

	(void)argc;
	(void)argv;
	env = mst_alloc_env(envp);
	cmd = NULL;
	while (1)
	{
		line = readline("minichaise> ");
		if (*line)
			add_history(line);
		tokens = parser(line);
		token = (t_token *) tokens->content;
		cmd = get_command(token->data);
		exec(cmd, &env);
		free(line);
	}
	rl_clear_history();
	mst_clear(&env);
	return (0);
}
	// char *arr[] = {"25", "20", "22", "10", "12", "15", "05", "01",
	// 	"08", "36", "30", "28", "40", "38", "48", "45", "50", NULL};

	// nb_mst = mst_alloc_env(arr);
	// debug_node(mst_get_node(nb_mst, argv[1]));

	// env = mst_alloc_env(envp);
	// mst_delete(&env, argv[1]);
	// mst_display(env);

	// // printf("[%s]\n", env_cpy[0]);

	// // cmds = parser(argv[1]);
	// // token = (t_token *)cmds->content;
	// // cmd = get_command(token->data);

	// // // token_display_command(cmd);
	// // exec(cmd, &env);
	// mst_clear(&env);
	// // ft_lstclear2(&cmds, token_destroy);
	// return (0);
