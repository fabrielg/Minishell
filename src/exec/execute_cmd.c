#include "exec.h"
#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

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

int	child_exec(t_command *cmd, t_minishell *ms)
{
	t_builtin	f;
	char		*path;
	char		**env_cpy;

	f = NULL;
	if (redirect_cmd(cmd) == ERROR)
		return (REDIR_ERROR);
	f = get_builtin(cmd->args[0], NULL);
	if (f)
		return (f(cmd->args, &(ms->exports)));
	path = research_path(cmd->args[0],
	mst_get_node(ms->exports, "PATH")->dic.value);
	env_cpy = env_newtab(ms->exports);
	execve(path, cmd->args, env_cpy);
	free(path);
	return (CMD_NOT_FOUND);
}

int	execute_cmd(t_command *cmd, t_minishell *ms)
{
	pid_t			pid;
	int				status;
	unsigned char	exit_code;

	if (!cmd)
		return (CMD_NOT_FOUND);
	pid = fork();
	if (pid == -1)
		return (ERROR);
	if (pid == 0)
	{
		exit_code = child_exec(cmd, ms);
		exit(clear_minishell(ms, exit_code));
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
	}
	return (SUCCESS);
}
