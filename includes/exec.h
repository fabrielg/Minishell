#ifndef EXEC_H
# define EXEC_H

# include "envp.h"
# include "libft.h"

# define ERROR -1
# define SUCCESS 1
# define REDIR_ERROR 1
# define CMD_NOT_FOUND 127
# define PERM_DENIED 126

typedef struct s_mst	t_mst;
typedef int	(*t_builtin)(t_list2 *args, t_mst **env);

//BUILT-INS___________________________

int	cmd_echo(t_list2 *args, t_mst **env);
int	cmd_cd(t_list2 *args, t_mst **env);
int	cmd_pwd(t_list2 *args, t_mst **env);
int	cmd_export(t_list2 *args, t_mst **env);
int	cmd_unset(t_list2 *args, t_mst **env);
int	cmd_env(t_list2 *args, t_mst **env);
int	cmd_exit(t_list2 *args, t_mst **env);

//EXEC

char	**list2_to_tab(t_list2 *lst);
int		redirect_cmd(t_command *cmd);
int		execute_cmd(t_command *cmd, t_mst **env);
char	*research_path(char *cmd, char *env_path);

#endif
