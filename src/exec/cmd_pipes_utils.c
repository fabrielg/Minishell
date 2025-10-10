#include "exec.h"
#include "minishell.h"

void	close_pipes(t_command *cmd)
{
	if (cmd->pipes[0] > 2)
		close(cmd->pipes[0]);
	if (cmd->pipes[1] > 2)
		close(cmd->pipes[1]);
}

int	pipe_cmd(t_command *cmd)
{
	int	i;

	i = -1;
	while (++i < 2)
	{
		if (cmd->pipes[i] > 2)
		{
			if (dup2(cmd->pipes[i], i) == -1)
				return (perror("dup2"), 1);
			close(cmd->pipes[i]);
		}
	}
	return (0);
}
