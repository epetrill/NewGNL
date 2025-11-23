/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epetrill <epetrill@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:22:36 by epetrill          #+#    #+#             */
/*   Updated: 2025/11/23 22:57:29 by epetrill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t	ft_strlen(const char *str);
char	*ft_strjoin_mod(char *s1, char const *s2);
int		ft_strchr_mod(const char *s);
int		ft_read(int fd, char **res, char *buffer, int i);
int		ft_rest(char *res, char *buffer);
char	*get_next_line(int fd);

#endif