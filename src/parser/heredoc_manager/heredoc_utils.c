/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:21:37 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:21:37 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "sig.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <readline/readline.h>

/**
 * @brief Generates a temporary filename for a heredoc.
 * @return Allocated string with heredoc path (must be freed)
 */
char	*get_heredoc_name(int heredoc_id)
{
	char	*id_txt;
	char	*fd_name;

	id_txt = ft_itoa(heredoc_id);
	fd_name = ft_strjoin(HEREDOC_PATH, id_txt);
	free(id_txt);
	return (fd_name);
}

/**
 * @brief Handles exit status of heredoc process and cleans up file if error.
 * @return 0 on normal exit, 1 if interrupted or error
 */
int	heredoc_exit_status(int status, t_redirect *rdr, t_minishell *ms)
{
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
	{
		ms->last_exit_code = 0;
		return (0);
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		ms->last_exit_code = 130;
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		ms->last_exit_code = WEXITSTATUS(status);
	unlink(rdr->file);
	free(rdr->file);
	rdr->file = NULL;
	return (1);
}

/**
 * @brief Prints a warning for heredoc prematurely terminated by EOF.
 */
static void	heredoc_err(int line_count, char *limiter)
{
	char	*str;

	str = ft_itoa(line_count);
	write(STDERR_FILENO, "warning : here-document at line ", 32);
	if (str)
	{
		write(STDERR_FILENO, str, ft_strlen(str));
		free(str);
	}
	write(STDERR_FILENO, " delimited by end-of-file (wanted `", 35);
	write(STDERR_FILENO, limiter, ft_strlen(limiter));
	write(STDERR_FILENO, "')\n", 3);
}

/**
 * @brief Reads lines from stdin until heredoc limiter is reached.
 *        Writes input to given file descriptor.
 */
void	heredoc_read_loop(int fd, char *limiter)
{
	char		*line;
	static int	line_count = 1;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		line_count++;
		if (!strcmp(line, limiter))
			return (free(line));
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	heredoc_err(line_count, limiter);
}
