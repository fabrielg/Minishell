#include "exec.h"

static int	redirect_out(t_redirect *rdr, int flags)
{
	int	fd;

	fd = open(rdr->file->text, flags, 0644);
	if (fd == -1)
		return (ERROR);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), ERROR);
	return (close(fd), SUCCESS);
}

static int	redirect_in(t_redirect *rdr)
{
	int	fd;

	fd = open(rdr->file->text, O_RDONLY);
	if (fd == -1)
		return (ERROR);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), ERROR);
	return (close(fd), SUCCESS);
}

static int	redirect_heredoc(t_redirect *rdr)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (ERROR);
	if (write(fd[1], rdr->file->text, ft_strlen(rdr->file->text)) == -1)
		return (close(fd[1]), close(fd[0]), ERROR);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (close(fd[0]), ERROR);
	return (close(fd[0]), SUCCESS);
}

int	redirect_cmd(t_command *cmd)
{
	int			i;
	t_redirect	*rdr;
	t_list2		*curr;
	int			ret;

	i = -1;
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
