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

int	execute_cmd(t_command *cmd, t_mst **env)
{
	pid_t		pid;
	int			status;
	t_builtin	f;
	char		*path;
	char		**env_cpy;

	pid = fork();
	f = NULL;
	if (pid == -1)
		return (ERROR);
	if (pid == 0)
	{
		if (redirect_cmd(cmd) == ERROR)
			exit(REDIR_ERROR);
		f = get_builtin(cmd->args[0]);
		if (f)
			exit(f(cmd->args, env));
		path = research_path(cmd->args[0], mst_get_node(*env, "PATH")->dic->value);
		env_cpy = env_newtab(*env);
		execve(path, cmd->args, env_cpy);
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
