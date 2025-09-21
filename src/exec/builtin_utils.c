#include "exec.h"
#include <errno.h>
#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

int	handle_exit(t_command *cmd, t_minishell *ms, unsigned char *exit_code)
{
	if (cmd->argc == 1)
		*exit_code = ms->last_exit_code;
	if ((cmd->argc >= 2 && *exit_code != 1) || cmd->argc == 1)
		return (*exit_code);
	return (-1);
}

t_builtin	get_builtin(char *name, unsigned char *flag)
{
	if (!ft_strcmp(name, "echo"))
		return (cmd_echo);
	else if (!ft_strcmp(name, "cd"))
		return (cmd_cd);
	else if (!ft_strcmp(name, "pwd"))
		return (cmd_pwd);
	else if (!ft_strcmp(name, "export"))
		return (cmd_export);
	else if (!ft_strcmp(name, "unset"))
		return (cmd_unset);
	else if (!ft_strcmp(name, "env"))
		return (cmd_env);
	else if (!ft_strcmp(name, "exit"))
	{
		if (flag)
			*flag = F_EXIT;
		return (cmd_exit);
	}
	return (NULL);
}
