/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:28:47 by ephantom          #+#    #+#             */
/*   Updated: 2021/12/17 17:25:34 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s != '\0')
	{
		write(fd, s, 1);
		s++;
	}
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen((char *)s1);
	str = malloc(sizeof(char) * (len + ft_strlen((char *)s2) + 1));
	if (!str)
		return (NULL);
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	free((void *)(s1 - len));
	return (str);
}

int	get_next_line(char **line, int fd)
{
	int		bytes_buf;
	char	buffer[2];

	bytes_buf = 0;
	*line = malloc(1);
	if (!(*line))
		return (-1);
	(*line)[0] = '\0';
	buffer[1] = '\0';
	while ((read(fd, buffer, 1)) > 0)
	{
		bytes_buf = 1;
		*line = ft_strjoin_gnl((*line), buffer);
		if (buffer[0] == '\n')
			break ;
	}
	if (!bytes_buf)
		free(*line);
	return (bytes_buf);
}
