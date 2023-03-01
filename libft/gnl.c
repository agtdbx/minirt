/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:37:27 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/01 14:54:39 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_gnl_rec(int fd, int len, char *save);

char	*get_next_line(int fd)
{
	static char	save[OPEN_MAX][BUFFER_SIZE + 1] = {0};
	char		head[BUFFER_SIZE + 1];
	char		*line;
	int			len;

	if (fd < 0 || OPEN_MAX < fd)
		return (NULL);
	ft_strlcpy(head, save[fd], BUFFER_SIZE + 1);
	len = ft_strcspn(head, "\n");
	if (head[len] == '\n')
	{
		line = ft_substr(head, 0, len + 1);
		if (line == NULL)
			return (NULL);
		ft_strlcpy(save[fd], head + len + 1, BUFFER_SIZE + 1);
		return (line);
	}
	line = ft_gnl_rec(fd, len, save[fd]);
	if (line == NULL)
		return (NULL);
	ft_memcpy(line, head, len);
	return (line);
}

static char	*ft_gnl_rec(int fd, int len, char *save)
{
	char	buf[BUFFER_SIZE + 1];
	char	*line;
	int		rlen;

	rlen = read(fd, buf, BUFFER_SIZE);
	if (rlen == -1)
		return (NULL);
	buf[rlen] = '\0';
	if (rlen == 0 && len == 0)
		return (NULL);
	rlen = ft_strcspn(buf, "\n");
	rlen += (buf[rlen] == '\n');
	if (rlen != BUFFER_SIZE || buf[rlen - 1] == '\n')
	{
		line = ft_calloc(len + rlen + 1, sizeof(char));
		ft_strlcpy(save, buf + rlen, BUFFER_SIZE + 1);
	}
	else
		line = ft_gnl_rec(fd, len + BUFFER_SIZE, save);
	if (line == NULL)
		return (NULL);
	ft_memcpy(line + len, buf, rlen);
	return (line);
}
