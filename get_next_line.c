/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epetrill <epetrill@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:22:30 by epetrill          #+#    #+#             */
/*   Updated: 2025/11/23 22:57:45 by epetrill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	ft_read(int fd, char **res, char *buffer, int i)
{
	int	j;
	int	ret;

	j = 0;
	ret = 1;
	i = ft_strchr_mod(*res);
	while (i == -1 && ret > 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		buffer[ret] = '\0';
		*res = ft_strjoin_mod(*res, buffer);
		if (*res == NULL)
			return (-1);
		i = ft_strchr_mod(*res);
	}
	if (i != -1)
		(*res)[i] = '\0';
	if (ret > 0 && i != -1)
	{
		i = ft_strchr_mod(buffer);
		while (buffer[i])
			buffer[j++] = buffer[1 + i++];
		buffer[j] = '\0';
	}
	return (ret);
}

int	ft_rest(char *res, char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	res[i] = '\0';
	while (i-- > 0)
		res[i] = buffer[i];
	i = ft_strchr_mod(buffer);
	if (i != -1)
	{
		if (buffer[i] == '\n')
			i++;
		while (buffer[i])
			buffer[j++] = buffer[i++];
		buffer[j] = '\0';
		return (1);
	}
	return (0);
}

char *get_next_line(int fd)
{
	static char	*buffer;
	char		*res;
	int			ret;

	ret = 1;
	if (BUFFER_SIZE <= 0 || read(fd, 0, 0))
		return (NULL);
	res = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!res)
		return (NULL);
	res[0] = '\0';
	if (!(buffer))
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (NULL);
		ret = ft_read(fd, &res, buffer, 0);
	}
	else
	{
		if (ft_rest(res, buffer) == 0)
			ret = ft_read(fd, &res, buffer, 0);
	}
	if (ret > 0)
		return (res);
	free(buffer);
	buffer = NULL;
	if (ret == 0)
		return (res);
	return (NULL);
}
/*
int	main(void)
{
	int		fd;
	char	*str;

	fd = open("test.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("%s", str);
	str = get_next_line(fd);
	printf("%s", str);
	str = get_next_line(fd);
	printf("%s", str);
	close(fd);
	free(str);
	return (0);
}
*/