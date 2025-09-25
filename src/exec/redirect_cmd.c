#include "exec.h"
#include <fcntl.h>

/**
 * @brief Redirects STDOUT to a file (truncate or append mode).
 * @param rdr   Redirection descriptor (contains file path)
 * @param flags Flags for open() (e.g., O_TRUNC or O_APPEND)
 * @return SUCCESS or ERROR
 */
static int	redirect_out(t_redirect *rdr, int flags)
{
	int	fd;

	fd = open(rdr->file, flags, 0644);
	if (fd == -1)
		return (ERROR);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), ERROR);
	return (close(fd), SUCCESS);
}

/**
 * @brief Redirects STDIN from a file.
 * @param rdr Redirection descriptor (contains file path)
 * @return SUCCESS or ERROR
 */
static int	redirect_in(t_redirect *rdr)
{
	int	fd;

	fd = open(rdr->file, O_RDONLY);
	if (fd == -1)
		return (ERROR);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), ERROR);
	return (close(fd), SUCCESS);
}

/**
 * @brief Redirects STDIN from a heredoc string using a pipe.
 * @param rdr Redirection descriptor (contains heredoc content)
 * @return SUCCESS or ERROR
 */
static int	redirect_heredoc(t_redirect *rdr)
{
	int	fd;

	fd = open(rdr->file, O_RDONLY);
	unlink(rdr->file);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), ERROR);
	return (close(fd), SUCCESS);
}

/**
 * @brief Applies all redirections attached to a command.
 * @return SUCCESS if all redirections succeed, otherwise ERROR
 */
int	redirect_cmd(t_command *cmd)
{
	t_redirect	*rdr;
	t_list2		*curr;
	int			ret;

	ret = -1;
	curr = cmd->redirects;
	while (curr)
	{
		rdr = get_redir(curr->content);
		if (rdr->type == REDIRECT_INPUT)
			ret = redirect_in(rdr);
		else if (rdr->type == REDIRECT_OUTPUT)
			ret = redirect_out(rdr, O_WRONLY | O_CREAT | O_TRUNC);
		else if (rdr->type == REDIRECT_APPEND)
			ret = redirect_out(rdr, O_WRONLY | O_CREAT | O_APPEND);
		else if (rdr->type == REDIRECT_HEREDOC)
			ret = redirect_heredoc(rdr);
		if (ret == ERROR)
			return (ERROR);
		curr = curr->next;
	}
	return (SUCCESS);
}
