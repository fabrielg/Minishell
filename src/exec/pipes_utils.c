#include "exec.h"
#include "minishell.h"

/**
 * @brief Closes the pipe file descriptors of a command if they are open.
 */
void	close_opened_pipes(t_command *cmd)
{
	if (cmd->pipes[0] > 2)
		close(cmd->pipes[0]);
	if (cmd->pipes[1] > 2)
		close(cmd->pipes[1]);
}

/**
 * @brief Duplicates the pipe FDs to stdin/stdout and closes the originals.
 * @return 0 on success, 1 on dup2 failure
 */
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
