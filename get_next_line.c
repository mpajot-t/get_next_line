/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpajot-t <mpajot-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:28:08 by mpajot-t          #+#    #+#             */
/*   Updated: 2024/11/19 10:10:50 by mpajot-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char *stash)
{
	int		i;
	int		j;
	char	*line;

	if (!stash)
		return (NULL);
	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*update_stash(char *stash)
{
	char	*new_stash;
	int		i;
	int		j;

	j = 0;
	i = ft_strlen_nl(stash);
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = malloc((ft_strlen(stash) - i + 1) * sizeof(char));
	if (!new_stash)
		return (NULL);
	while (stash[i + j])
	{
		new_stash[j] = stash[i + j];
		j++;
	}
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

static char	*read_and_stash(int fd, char *stash, char *buffer)
{
	char	*temp;
	int		readed;

	readed = 1;
	while (!ft_strchr(stash, '\n') && readed > 0)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
		{
			free(stash);
			return (NULL);
		}
		buffer[readed] = '\0';
		if (readed == 0)
			break ;
		if (!stash)
		{
			stash = malloc(sizeof(char));
			stash[0] = '\0';
		}
		temp = ft_strjoin(stash, buffer);
		free(stash);
		stash = temp;
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char		*stash;
	char			*line;
	char			*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	stash = read_and_stash(fd, stash, buffer);
	free(buffer);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = update_stash(stash);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>
int main()
{
    int     fd;
    char    *line;

    system("echo 'Première ligne\nDeuxième ligne\nTroisième ligne' > test.txt");

    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return (1);
    }

    // Premier appel - première ligne
    line = get_next_line(fd);
    printf("1ère ligne : %s", line);
    free(line);

    // Deuxième appel - deuxième ligne
    line = get_next_line(fd);
    printf("2ème ligne : %s", line);
    free(line);

    // Troisième appel - troisième ligne
    line = get_next_line(fd);
    printf("3ème ligne : %s", line);
    free(line);

    close(fd);
    return (0);
}
*/