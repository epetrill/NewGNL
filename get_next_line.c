/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epetrill <epetrill@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:26:25 by epetrill          #+#    #+#             */
/*   Updated: 2025/11/25 18:40:46 by epetrill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*set_line(char *f_line)
{
	char	*rest;
	size_t	i;

	i = 0;
	while (f_line[i] && f_line[i] != NEW_LINE)
		i++;
	if (f_line[i] == 0)
		return (NULL);
	rest = ft_substr(f_line, i + 1, ft_strlen(f_line) - i);
	if (*rest == 0)
	{
		free(rest);
		rest = NULL;
	}
	f_line[i + 1] = 0;
	return (rest);
}

static char	*fill_line(int fd, char *rest, char *buffer)
{
	size_t	nb_read;
	char	*tmp;

	nb_read = 1;
	while (nb_read > 0)
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read == 0)
			break ;
		buffer[nb_read] = 0;
		if (!rest)
			rest = ft_strdup("");
		tmp = rest;
		rest = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(buffer, NEW_LINE))
			break ;
	}
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(rest);
		rest = NULL;
		return (NULL);
	}
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = fill_line(fd, rest, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	rest = set_line(line);
	return (line);
}
