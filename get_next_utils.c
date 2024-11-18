/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpajot-t <mpajot-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:28:13 by mpajot-t          #+#    #+#             */
/*   Updated: 2024/11/18 10:44:22 by mpajot-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
    if (!str)
        return (0);
    while (str[i] && str[i] != '\n')
        i++;
	if (str[i] == '\n')
		i++;
    return (i);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*ns;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	ns = malloc(len * sizeof(char));
	if (!ns)
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			ns[i] = s1[i];
			i++;
		}
	}
	while (s2[j])
	{
		ns[i + j] = s2[j];
		j++;
	}
	ns[i + j] = '\0';
	if (s1)
		free(s1);
	return (ns);
}
