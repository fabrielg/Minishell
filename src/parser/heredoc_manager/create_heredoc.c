#include "minishell.h"
#include "parser.h"
#include "sig.h"
#include <fcntl.h>
#include <sys/wait.h>

/**
 * @brief Reads heredoc input from stdin until limiter and writes to file.
 *        Runs in a child process.
 */
static void	read_heredoc(char *limiter, t_redirect *rdr, t_minishell *ms)
{
	int		fd;

	if (!rdr->file)
		exit(clear_minishell(ms, 1));
	reset_signals();
	fd = open(rdr->file, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (fd == -1)
		exit(clear_minishell(ms, 1));
	heredoc_read_loop(fd, limiter);
	free(limiter);
	close(fd);
	exit(clear_minishell(ms, 0));
}

/**
 * @brief Creates a heredoc by forking a process to read input until limiter.
 * @return 0 on success, 1 on failure or interruption
 */
int	create_heredoc(t_redirect *rdr, t_minishell *ms)
{
	pid_t		pid;
	int			status;
	char		*limiter;
	static int	heredoc_id = 0;

	heredoc_id++;
	limiter = rdr->file;
	rdr->file = get_heredoc_name(heredoc_id);
	if (!rdr->file)
		return (1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		read_heredoc(limiter, rdr, ms);
	g_sig_pid = pid;
	waitpid(pid, &status, 0);
	signal(SIGINT, &handle_sigint);
	g_sig_pid = 0;
	free(limiter);
	return (heredoc_exit_status(status, rdr, ms));
}
