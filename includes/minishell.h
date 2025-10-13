/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 02:06:44 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/13 22:01:36 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "envp.h"
# include "tokens.h"
# include "ast.h"
# include <sys/types.h>

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

/* Main structure containing all shell data */
typedef struct s_minishell
{
	char			*shell_name;
	t_mst			*exports;
	char			*input_line;

	t_ast			*ast_root;
	t_list2			*tokens;
	unsigned char	last_exit_code;
	int				shell_exit_code;
	bool			signal_received;
	bool			in_pipe;
	pid_t			*child_pids;
	int				(*pipes)[2];
	int				stdin_backup;
	int				stdout_backup;
}	t_minishell;

//[MINISHELL-UTILS]_________________________________________

void		init_minishell(t_minishell *ms, char **envp);
t_uint8		clear_minishell(t_minishell *ms, t_uint8 exit_code);


//[LINE-UTILS]_________________________________________
int			is_end_of_file(char *input_line);
void		handle_prompt_signal(t_uint8 *exit_code);
int			process_line(t_minishell *ms);

//[ERROR-FUNCS]______________________________________________

int			exec_err(char *cmd, char *msg, t_uint8 exit_code);
t_uint8		cmd_err(t_uint8 *exit_code, char *arg, char *err_msg, int code);
t_uint8		set_err(t_uint8 *exit_code, t_uint8 new);

#endif
