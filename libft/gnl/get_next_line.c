/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:54:41 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/02/23 15:48:44 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	buffer_alloc(char **buffer)
{
	if (*buffer == NULL)
		*buffer = ft_calloc(1, sizeof(char));
	if (*buffer == NULL)
		return (0);
	return (1);
}

void	read_file(int fd, char **buffer)
{
	char	*content;
	int		nb_read;

	if (!buffer_alloc(buffer))
		return ;
	if (ft_has_char(*buffer, '\n') != -1)
		return ;
	content = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!content)
		return ;
	while (1)
	{
		nb_read = read(fd, content, BUFFER_SIZE);
		content[nb_read] = 0;
		if (nb_read <= 0)
		{
			if (ft_strlen(*buffer) == 0)
				return (free(*buffer), *buffer = NULL, free(content));
			break ;
		}
		gnl_strjoin(buffer, content);
		if (nb_read < BUFFER_SIZE || ft_has_char(*buffer, '\n') != -1)
			break ;
	}
	free(content);
}

static void	gnl_clear(char **buffer)
{
	size_t	i;

	i = 0;
	while (i < GNL_FD_SIZE)
	{
		if (buffer[i])
			free(buffer[i]);
		buffer[i] = NULL;
		i++;
	}
}

char	*get_next_line(int fd)
{
	static char	*buffer[GNL_FD_SIZE];
	char		*line;

	if (fd == -42 || read(fd, 0, 0) < 0)
	{
		if (fd == -42)
		{
			gnl_clear(buffer);
			return (NULL);
		}
		if ((fd < 0 || fd > GNL_FD_SIZE))
			return (NULL);
		if (buffer[fd])
			free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	read_file(fd, &buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = NULL;
	gnl_strcut(&buffer[fd], &line);
	if (!line)
		free(buffer[fd]);
	return (line);
}
