#include "minishell.h"
#include "parser.h"
#include "fcntl.h"
#include "expander.h"

/**
 * @brief Appends n bytes from buf to the existing content buffer.
 * @return Newly allocated buffer containing the concatenated content,
 *         or NULL on allocation failure
 */
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

/**
 * @brief Reads the entire content of a file into a string.
 * @return Allocated string with file content, or NULL on error
 */
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
	n = read(fd, buf, sizeof(buf));
	while (n > 0)
	{
		content = append_buffer(content, size, buf, n);
		if (!content)
			return (close(fd), NULL);
		size += n;
		n = read(fd, buf, sizeof(buf));
	}
	close(fd);
	return (content);
}

/**
 * @brief Overwrites a file with the given content.
 * @return 0 on success, 1 on error
 */
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

/**
 * @brief Expands variables in a heredoc file content.
 * @return 0 on success, 1 on error
 */
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
