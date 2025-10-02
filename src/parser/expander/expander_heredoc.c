#include "minishell.h"
#include "parser.h"
#include "fcntl.h"
#include "expander.h"

static char	*append_buffer(char *content, size_t size,
		const char *buf, ssize_t n)
{
	char	*tmp;

	tmp = malloc(size + n + 1);
	if (!tmp)
		return (free(content), NULL);
	if (content)
	{
		ft_memcpy(tmp, content, size);
		free(content);
	}
	ft_memcpy(tmp + size, buf, n);
	tmp[size + n] = '\0';
	return (tmp);
}

static char	*read_file_content(const char *path)
{
	int		fd;
	ssize_t	n;
	size_t	size;
	char	buf[1024];
	char	*content;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	content = NULL;
	size = 0;
	while ((n = read(fd, buf, sizeof(buf))) > 0)
	{
		content = append_buffer(content, size, buf, n);
		if (!content)
			return (close(fd), NULL);
		size += n;
	}
	close(fd);
	return (content);
}

static int	write_file_content(const char *path, const char *content)
{
	int	fd;

	fd = open(path, O_WRONLY | O_TRUNC);
	if (fd == -1)
		return (perror("open heredoc rewrite"), 1);
	if (write(fd, content, ft_strlen(content)) == -1)
	{
		close(fd);
		return (perror("write heredoc"), 1);
	}
	close(fd);
	return (0);
}

int	expand_heredoc(t_redirect *redir, t_mst *env, int exit_code)
{
	char	*content;

	if (!redir || redir->type != REDIRECT_HEREDOC)
		return (0);
	content = read_file_content(redir->file);
	if (!content)
		return (0);
	expand_arg(&content, env, exit_code);
	if (write_file_content(redir->file, content))
		return (free(content), 1);
	free(content);
	return (0);
}
