/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 22:15:10 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/09/08 22:19:20 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_tab(char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return (0);
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (0);
}

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**cpy_env(char **env)
{
	char	**env_cpy;
	int		i;

	i = -1;
	env_cpy = calloc(tab_len(env) + 1, sizeof(char *));
	if (!env_cpy)
		return (NULL);
	while (env[++i])
	{
		env_cpy[i] = ft_strdup(env[i]);
		if (!env_cpy[i])
			return (free_tab(env_cpy), NULL);
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

int	main(int argc, char *argv[], char **envp)
{
	t_mst		*env;
	t_list2		*cmds;
	t_command	*cmd;
	t_token		*token;


	if (argc != 2)
		return (0);
	env = mst_alloc_env(envp);
	// printf("[%s]\n", env_cpy[0]);

	cmds = parser(argv[1]);
	token = (t_token *)cmds->content;
	cmd = get_command(token->data);
	// token_display_command(cmd);
	exec(cmd, &env);
	// printf("\n\n\n");
	// bst_display(env);
	mst_clear(&env);
	ft_lstclear2(&cmds, token_destroy);
	return (0);
}
