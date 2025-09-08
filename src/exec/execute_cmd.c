#include "exec.h"

t_builtin	get_builtin(char *name)
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
		return (cmd_exit);
	return (NULL);
}

int	execute_cmd(t_command *cmd, char ***env)
{
	pid_t		pid;
	int			status;
	t_builtin	f;
	char		*path;

	pid = fork();
	if (pid == -1)
		return (ERROR);
	if (pid == 0)
	{
		if (redirect_cmd(cmd) == ERROR)
			exit(REDIR_ERROR);
		f = get_builtin(cmd->args[0]);
		if (f)
			exit(f(cmd->arg_count - 1, cmd->args + 1, env));
		path = research_path(cmd->args[0], getenv("PATH")); //TODO : getenv
		execve(path, cmd->args + 1, *env);
		//TODO : print error
		free(path);
		exit(CMD_NOT_FOUND);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WIFEXITED(status));
	}
	return (SUCCESS);
}
