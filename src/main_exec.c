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
	char	**env_cpy;
	t_mst		*env;
	t_list2		*cmds;
	t_command	*cmd;
	t_token		*token;


	(void)argc;
	env_cpy = cpy_env(envp);
	env = mst_alloc_env(envp);

	cmds = parser(argv[1]);
	token = (t_token *)cmds->content;
	cmd = get_command(token->data);
	// token_display_command(cmd);

	execute_cmd(cmd, &env);
	free_tab(env_cpy);
	return (0);
}
