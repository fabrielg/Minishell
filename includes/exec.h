/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:25:34 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:26:42 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "envp.h"
# include "libft.h"
# include "tokens.h"
# include "ast.h"

# define ERROR -1
# define SUCCESS 1

# define REDIR_ERR 1
# define NOT_FOUND_ERR 127
# define PERM_ERR 126

# define F_EXIT 0b1
# define PATH_MAX_LEN 4096

# define NO_PATH_MSG   "No such file or directory\n"
# define NOT_FOUND_MSG "Command not found\n"
# define NO_PERM_MSG   "Permission denied\n"
# define IS_DIR_MSG    ": Is a directory\n"

typedef struct s_mst		t_mst;
typedef struct s_minishell	t_minishell;
typedef t_uint8				(*t_builtin)(char **args, t_mst **env);

//[BUILT-INS]_________________________________________

t_uint8		cmd_echo(char **args, t_mst **env);
t_uint8		cmd_cd(char **args, t_mst **env);
t_uint8		cmd_pwd(char **args, t_mst **env);
t_uint8		cmd_export(char **args, t_mst **env);
t_uint8		cmd_unset(char **args, t_mst **env);
t_uint8		cmd_env(char **args, t_mst **env);
t_uint8		cmd_exit(char **args, t_mst **env);

//[BUILTIN_UTILS]_____________________________________

t_builtin	get_builtin(char *name, t_uint8 *flag_out);
int			handle_exit(t_command *cmd, t_minishell *ms, t_uint8 *exit_code);

//[ENV_UTILS]_________________________________________

char		*research_path(char *cmd, char *env_path);

//[FORK_UTILS]________________________________________

int			cmd_exit_status(int status, t_minishell *ms);
int			redirect_cmd(t_command *cmd);
t_uint8		is_builtin(char **args, t_mst **env, t_uint8 *exit_code);
t_uint8		is_abs_rltv_path(char **args, t_minishell *ms, t_uint8 *exit_code);
t_uint8		no_shebang_case(char *ag, char **e, t_uint8 *code, t_minishell *ms);
t_uint8		is_in_path(char **ag, t_mst *path, t_minishell *ms, t_uint8 *code);

//[PIPE_UTILS]________________________________________

int			pipe_cmd(t_command *cmd);
void		close_opened_pipes(t_command *cmd);
int			pipe_clear(int (*pipes)[2], pid_t *pids);
int			wait_forked_pipes(t_minishell *ms, pid_t *pids, int nb_cmds);
int			exec_init_pipes(int (*pipes)[2], int nb_cmd);
void		exec_close_pipes(int (*pipes)[2], int nb_cmds);
int			ap_pipes(int (*pipes)[2], pid_t *pid, t_ast *node, t_minishell *ms);

//[RUNTIME]___________________________________________

int			exec_ast(t_ast *node, t_minishell *ms);
int			exec_command(t_command *cmd, t_minishell *ms);
int			exec_pipeline(t_ast *node, t_minishell *ms);
int			exec_logical(t_ast *node, t_minishell *ms);
int			exec_subshell(t_ast *node, t_minishell *ms);

//[RUNTIME_UTILS]_____________________________________

int			run_cmd(t_command *cmd, t_minishell *ms);
int			run_one_builtin(t_command *cmd, t_minishell *ms);

#endif
