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

	pid = fork();
	if (pid == -1)
		return (ERROR);
	if (pid == 0)
	{
		if (redirect_cmd(cmd) == ERROR)
			exit(REDIR_ERROR);
		f = get_builtin(get_word(cmd->args->content)->text);
		if (f)
			exit(f(cmd->args + 1, env));
		path = research_path(get_word(cmd->args->content)->text, mst_get_node(*env, "PATH")->dic->value); //TODO : getenv
		printf("path : [%s]\n", path);
		// execve(path, list2_to_tab(cmd->args), *env);
		printf("fail\n");
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
