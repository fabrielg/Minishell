/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 02:06:44 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/09/19 19:16:30 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "envp.h"
# include "tokens.h"
# include <sys/types.h>

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

/* Main structure containing all shell data */
typedef struct s_minishell
{
	t_mst		*exports;				/* Exported variables (KEY=VALUE format) */

	// TODO: t_ast	*ast_root;			/* Root of AST */
	char			*input_line;			/* Raw input line from readline */
	t_list2			*tokens;				/* List of tokens after parsing */

	/* Return codes and status */
	unsigned char	last_exit_code;			/* Return code of last command ($?) */
	int				shell_exit_code;		/* Return code of last command ($?) */

	/* History and readline */
	char			*shell_name;			/* The prompt display by readline */

	/* Signal management */
	int				signal_received;		/* Last signal received */
	bool			in_child_process;		/* To adapt signal behavior */

	/* Processes and pipes */
	pid_t			*child_pids;			/* PIDs of active child processes */
	int				pipe_fds[2];			/* File descriptors for pipes (temporary) */

	/* Session variables */
	int			stdin_backup;			/* Backup of FD for redirections */
	int			stdout_backup;			/* Backup of FD for redirections */
}	t_minishell;

void	init_minishell(t_minishell *ms, char **envp);
int		clear_minishell(t_minishell *ms, int exit_code);
int		exec_error(char *cmd, char *msg, int exit_code);

#endif
