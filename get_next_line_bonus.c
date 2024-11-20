/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpajot-t <mpajot-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:59:15 by mpajot-t          #+#    #+#             */
/*   Updated: 2024/11/19 11:37:29 by mpajot-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*extract_line(char *stash[], int fd)
{
	int		i;
	int		j;
	char	*line;

	if (!stash[fd])
		return (NULL);
	i = 0;
	j = 0;
	while (stash[fd][i] && stash[fd][i] != '\n')
		i++;
	if (stash[fd][i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = stash[fd][j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*update_stash(char *stash[], int fd)
{
	char	*new_stash;
	int		i;
	int		j;

	j = 0;
	i = ft_strlen_nl(stash[fd]);
	if (!stash[fd][i])
	{
		free(stash[fd]);
		return (NULL);
	}
	new_stash = malloc((ft_strlen(stash[fd]) - i + 1) * sizeof(char));
	if (!new_stash)
		return (NULL);
	while (stash[fd][i + j])
	{
		new_stash[j] = stash[fd][i + j];
		j++;
	}
	new_stash[j] = '\0';
	free(stash[fd]);
	return (new_stash);
}

static char	*read_and_stash(int fd, char *stash[], char *buffer)
{
	char	*temp;
	int		readed;

	readed = 1;
	while (!ft_strchr(stash[fd], '\n') && readed > 0)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
		{
			free(stash[fd]);
			return (NULL);
		}
		buffer[readed] = '\0';
		if (readed == 0)
			break ;
		if (!stash[fd])
		{
			stash[fd] = malloc(sizeof(char));
			stash[fd][0] = '\0';
		}
		temp = ft_strjoin(stash[fd], buffer);
		free(stash[fd]);
		stash[fd] = temp;
	}
	return (stash[fd]);
}

char	*get_next_line(int fd)
{
	static char		*stash[1024];
	char			*line;
	char			*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	stash[fd] = read_and_stash(fd, stash, buffer);
	free(buffer);
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash, fd);
	stash[fd] = update_stash(stash, fd);
	return (line);
}
