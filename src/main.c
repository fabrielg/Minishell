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
#include "parser.h"
#include "exec.h"
#include <readline/readline.h>
#include <readline/history.h>

void	init_minishell(t_minishell *ms, char **envp)
{
	ft_bzero(ms, sizeof(t_minishell));
	ms->exports = mst_alloc_env(envp);
	if (DEBUG_MODE)
		ms->shell_name = BLUE_B"Minichaise (debug) 🪑: "RESET;
	else
		ms->shell_name = WHITE_B"Minichaise 🪑: "RESET;
}

void	clear_minishell(t_minishell *ms)
{
	mst_clear(&ms->exports);
	ft_lstclear2(&ms->tokens, token_destroy);
	if (ms->input_line)
		free(ms->input_line);
}

int	main(int argc, char *argv[], char **envp)
{
	t_minishell	ms;

	(void)argc;
	(void)argv;
	init_minishell(&ms, envp);
	while (1)
	{
		ms.input_line = readline(ms.shell_name);
		if (!ms.input_line)
			break; ;
		add_history(ms.input_line);
		ms.tokens = parser(ms.input_line, ms.exports, ms.last_exit_code);
		tokens_display(ms.tokens);
		t_token		*tok = (t_token *) ms.tokens->content;
		t_command *cmd = get_command(tok->data);
		exec(cmd, &ms.exports);
		ft_lstclear2(&ms.tokens, token_destroy);
		free(ms.input_line);
	}
	rl_clear_history();
	clear_minishell(&ms);
	return (0);
}
