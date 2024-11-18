/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpajot-t <mpajot-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:28:08 by mpajot-t          #+#    #+#             */
/*   Updated: 2024/11/18 10:51:12 by mpajot-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char *stash)
{
	
}

static char *update_stash(char *stash)
{
	
}

static char	*read_and_stash(int fd, char *stash, char *buffer)
{
	char	*temp;
	int		readed;

	readed = 1;
	while (readed > 0)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
		{
			free(stash);
			return (NULL);
		}
		if (readed == 0)
			break;
		if (!stash)
		{
			stash = malloc(sizeof(char));
			stash[0] = '\0';
		}
		temp = ft_strjoin(stash, buffer);
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
	line = extract_line(stash);
	stash = uptdate_stash(stash);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>
int main()
{
    int fd;
    char *line;

    // Créer un fichier de test
    system("echo 'Première ligne\nDeuxième ligne\nTroisième ligne' > test.txt");

    // Ouvrir le fichier
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return (1);
    }

	line = get_next_line(fd);
	printf("1er ligne : %s", line);
    free(line);
    // Lire le fichier ligne par ligne
	/*
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Ligne lue : %s", line);
        free(line);
    }
	*/
    // Fermer le fichier
    close(fd);
    return (0);
}