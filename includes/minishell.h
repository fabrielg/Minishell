/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabrielg <fabrielg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 02:06:44 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/08/17 23:00:06 by fabrielg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <sys/types.h>
# include "tokens.h"
# include "env.h"

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

/* Main structure containing all shell data */
typedef struct s_minishell
{
	char		**envp;					/* Copy of environment (modifiable) */
	char		**export_list;			/* Exported variables (KEY=VALUE format) */

	// TODO: t_ast	*ast_root;			/* Root of AST */
	t_token		*ast_root;				/* Root of the AST */
	char		*input_line;			/* Raw input line from readline */
	t_token		*tokens;				/* List of tokens after lexing */

	/* Return codes and status */
	int			last_exit_code;			/* Return code of last command ($?) */
	int			shell_exit_code;		/* Exit code of the shell */
	bool		should_exit;			/* Flag to terminate the shell */
	
	/* History and readline */
	char		**history;				/* Custom history */
	
	/* Signal management */
	int			signal_received;		/* Last signal received */
	bool		in_child_process;		/* To adapt signal behavior */
	
	/* Processes and pipes */
	pid_t		*child_pids;			/* PIDs of active child processes */
	int			pipe_fds[2];			/* File descriptors for pipes (temporary) */
	
	/* Session variables */
	char		*current_directory;		/* Current PWD */
	int			stdin_backup;			/* Backup of FD for redirections */
	int			stdout_backup;			/* Backup of FD for redirections */
	
	/* Debugging/Development */
	char		*shell_name;			/* Shell name for error messages */
}	t_minishell;

#endif