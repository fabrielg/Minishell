#include "minishell.h"
#include "parser.h"
#include "signal.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define HEREDOC_PATH "/tmp/minishell_heredoc_"

static char	*get_fd_name(int heredoc_id)
{
	char		*id_txt;
	char		*fd_name;

	id_txt = ft_itoa(heredoc_id);
	fd_name = ft_strjoin(HEREDOC_PATH, id_txt);
	free(id_txt);
	return (fd_name);
}

static void	read_heredoc(char *limiter, t_redirect *rdr, t_minishell *ms)
{
	char	*line;
	int		fd;

	if (!rdr->file)
		exit(clear_minishell(ms, 1));
	fd = open(rdr->file, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (fd == -1)
		exit(clear_minishell(ms, 1));
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, limiter) == 0)
			break ;
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	free(limiter);
	close(fd);
	exit(clear_minishell(ms, 0));
}

int	create_heredoc(t_redirect *rdr, t_minishell *ms)
{
	pid_t		pid;
	int			status;
	char		*limiter;
	static int	heredoc_id = 0;

	heredoc_id++;
	limiter = rdr->file;
	rdr->file = get_fd_name(heredoc_id);
	if (!rdr->file)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		read_heredoc(limiter, rdr, ms);
	waitpid(pid, &status, 0);
	free(limiter);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (0);
	return (0);
}
