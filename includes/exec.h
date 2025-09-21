#ifndef EXEC_H
# define EXEC_H

# include "envp.h"
# include "libft.h"
# include "tokens.h"

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
typedef t_uint8	(*t_builtin)(char **args, t_mst **env);

//BUILT-INS___________________________

t_uint8			cmd_echo(char **args, t_mst **env);
t_uint8			cmd_cd(char **args, t_mst **env);
t_uint8		cmd_pwd(char **args, t_mst **env);
t_uint8		cmd_export(char **args, t_mst **env);
t_uint8		cmd_unset(char **args, t_mst **env);
t_uint8			cmd_env(char **args, t_mst **env);
t_uint8			cmd_exit(char **args, t_mst **env);

//EXEC

char		**list2_to_tab(t_list2 *lst);
int			redirect_cmd(t_command *cmd);
int			execute_cmd(t_command *cmd, t_minishell *ms);
int			execute_one_builtin(t_command *cmd, t_minishell *ms);
int			exec(t_command *cmd, t_minishell *ms);
t_builtin	get_builtin(char *name, t_uint8 *flag_out);
char		*research_path(char *cmd, char *env_path);
int			handle_exit(t_command *cmd, t_minishell *ms, t_uint8 *exit_code);

t_uint8		is_builtin(char **args, t_mst **env, t_uint8 *exit_code);
t_uint8		is_abs_rltv_path(char **args, t_mst *env, t_uint8 *exit_code);
t_uint8		is_in_path(char **args, t_mst *m_path, t_mst *env, t_uint8 *exit_code);


#endif
