#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

# define ERROR -1
# define SUCCESS 1
# define REDIR_ERROR 1
# define CMD_NOT_FOUND 127
# define PERM_DENIED 126

typedef int	(*t_builtin)(int argc, char **args, char ***env);

//BUILT-INS___________________________

int	cmd_echo(int argc, char **args, char ***env);
int	cmd_cd(int argc, char **args, char ***env);
int	cmd_pwd(int argc, char **args, char ***env);
int	cmd_export(int argc, char **args, char ***env);
int	cmd_unset(int argc, char **args, char ***env);
int	cmd_env(int argc, char **args, char ***env);
int	cmd_exit(int argc, char **args, char ***env);

//EXEC

int		redirect_cmd(t_command *cmd);
int		execute_cmd(t_command *cmd, char ***env);
char	*research_path(char *cmd, char *env_path);

#endif
