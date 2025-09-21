/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 22:15:10 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/09/21 03:21:51 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "exec.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char *argv[], char **envp)
{
	t_minishell		ms;
	t_token			*tok;
	t_command		*cmd;

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
		// tokens_display(ms.tokens);
		if(ms.tokens)
		{
			tok = (t_token *) ms.tokens->content;
			cmd = get_command(tok->data);
			exec(cmd, &ms);
			if (ms.shell_exit_code != -1)
				return (printf("exit_code : %i\n", ms.shell_exit_code), clear_minishell(&ms, ms.shell_exit_code));
			ft_lstclear2(&ms.tokens, token_destroy);
		}
		free(ms.input_line);
	}
	rl_clear_history();
	return (clear_minishell(&ms, 0));
}
