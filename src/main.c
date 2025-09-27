/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 22:15:10 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/09/27 18:04:55 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sig.h"
#include <readline/readline.h>

int	main(int argc, char *argv[], char **envp)
{
	t_minishell		ms;

	(void)argc;
	(void)argv;
	init_signals();
	init_minishell(&ms, envp);
	while (1)
	{
		ms.input_line = readline(ms.shell_name);
		if (is_end_of_file(ms.input_line))
			break ;
		handle_prompt_signal(&ms.last_exit_code);
		if (*ms.input_line)
			process_line(&ms);
		if (ms.shell_exit_code != -1)
			return (clear_minishell(&ms, ms.shell_exit_code));
		free(ms.input_line);
	}
	rl_clear_history();
	return (clear_minishell(&ms, 0));
}
