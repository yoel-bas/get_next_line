/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 01:09:38 by yoel-bas          #+#    #+#             */
/*   Updated: 2022/11/24 01:09:49 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_line(char *str)
{
	int		i;
	int		len;
	char	*s;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	len = i + 2;
	s = malloc(len);
	if (!s)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		s[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		s[i++] = '\n';
	s[i] = '\0';
	return (s);
}

static char	*full_line(char *str)
{
	char	*p;
	size_t	i;
	int		y;

	i = 0;
	y = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	if (i == ft_strlen(str))
		return (free(str), NULL);
	p = malloc((ft_strlen(str) - i) + 1);
	if (!p)
		return (NULL);
	while (str[i])
		p[y++] = str[i++];
	p[y] = '\0';
	return (free(str), str = NULL, p);
}

char	*get_next_line(int fd)
{
	char			*buff;
	static char		*str[OPEN_MAX];
	char			*line;
	int				i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!str[fd])
		str[fd] = ft_strdup("");
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	i = 1;
	while (i && !ft_strchr(str[fd], '\n'))
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i < 0)
			return (free(buff), free(str[fd]), str[fd] = NULL, NULL);
		buff[i] = '\0';
		str[fd] = ft_strjoin(str[fd], buff);
	}
	free(buff);
	line = get_line(str[fd]);
	str[fd] = full_line(str[fd]);
	return (line);
}
