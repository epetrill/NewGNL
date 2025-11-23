/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epetrill <epetrill@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:22:30 by epetrill          #+#    #+#             */
/*   Updated: 2025/11/21 17:07:33 by epetrill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	ft_read(int fd, char **res, char *buffer)
{
	int	i;
	int	j;
	int	ret;

	j = 0;
	ret = 1;
	while (((i = ft_strchr_mod(*res)) == -1) && ret > 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		buffer[ret] = '\0';
		if ((*res = ft_strjoin_mod(*res, buffer)) == NULL)
			return (-1);
	}
	i != -1 ? (*res)[i] = '\0' : 0;
	if (ret > 0 && i != -1)
	{
		i = ft_strchr_mod(buffer);
		while (buffer[i])
			buffer[j++] = buffer[1 + i++];
		buffer[j] = '\0';
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*ret;
	int			eol;

	eol = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		ret = ft_fill_strings(buffer, fd, &eol);
		if (eol == 1)
			return (ret);
		else
			get_next_line(fd);
	}
	else
	{
			
	}
	return (ret);
}

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("test.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("%s", str);
	close(fd);
	free(str);
	return (0);
}
