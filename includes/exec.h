#ifndef EXEC_H
# define EXEC_H

# include "envp.h"
# include "libft.h"
# include "tokens.h"

# define ERROR -1
# define SUCCESS 1
# define REDIR_ERROR 1
# define CMD_NOT_FOUND 127
# define PERM_DENIED 126
# define F_EXIT 0b1

typedef struct s_mst		t_mst;
typedef struct s_minishell	t_minishell;
typedef int	(*t_builtin)(char **args, t_mst **env);

//BUILT-INS___________________________

int			cmd_echo(char **args, t_mst **env);
int			cmd_cd(char **args, t_mst **env);
int			cmd_pwd(char **args, t_mst **env);
int			cmd_export(char **args, t_mst **env);
int			cmd_unset(char **args, t_mst **env);
int			cmd_env(char **args, t_mst **env);
int			cmd_exit(char **args, t_mst **env);

//EXEC

char		**list2_to_tab(t_list2 *lst);
int			redirect_cmd(t_command *cmd);
int			execute_cmd(t_command *cmd, t_minishell *ms);
int			execute_one_builtin(t_command *cmd, t_minishell *ms);
int			exec(t_command *cmd, t_minishell *ms);
t_builtin	get_builtin(char *name, unsigned char *flag_out);
char		*research_path(char *cmd, char *env_path);

#endif
