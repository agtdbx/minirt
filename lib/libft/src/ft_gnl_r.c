/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_r.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:42:20 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/03 08:52:46 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>

char		*ft_gnl_r(
				int fd,
				char save_buf[GNL_BUFFER_SIZE]);

static char	*ft_gnl_r_rec(
				int fd,
				char save_buf[GNL_BUFFER_SIZE],
				size_t len);

////////////////////////////////////////////////////////////////////////////////

char	*ft_gnl_r(
			int fd,
			char save_buffer[GNL_BUFFER_SIZE])
{
	char	head_buffer[GNL_BUFFER_SIZE];
	char	*line;
	int		line_len;

	ft_strlcpy(head_buffer, save_buffer, GNL_BUFFER_SIZE);
	line_len = ft_strcspn(head_buffer, "\n");
	if (head_buffer[line_len] == '\n')
	{
		line = ft_substr(head_buffer, 0, line_len + 1);
		if (line == NULL)
			return (NULL);
		ft_strlcpy(save_buffer, head_buffer + line_len + 1, GNL_BUFFER_SIZE);
		return (line);
	}
	line = ft_gnl_r_rec(fd, save_buffer, line_len);
	if (line == NULL)
		return (NULL);
	ft_memcpy(line, head_buffer, line_len);
	return (line);
}

static char	*ft_gnl_r_rec(
				int fd,
				char save_buffer[GNL_BUFFER_SIZE],
				size_t line_len)
{
	char	read_buffer[GNL_BUFFER_SIZE];
	char	*line;
	int		read_ret;

	read_ret = read(fd, read_buffer, GNL_BUFFER_SIZE - 1);
	if (read_ret == -1)
		return (NULL);
	read_buffer[read_ret] = '\0';
	if (read_ret == 0 && line_len == 0)
		return (NULL);
	read_ret = ft_strcspn(read_buffer, "\n");
	read_ret += (read_buffer[read_ret] == '\n');
	if (read_ret != GNL_BUFFER_SIZE || read_buffer[read_ret - 1] == '\n')
	{
		line = malloc(line_len + read_ret + 1);
		if (line != NULL)
			line[line_len + read_ret] = '\0';
		ft_strlcpy(save_buffer, read_buffer + read_ret, GNL_BUFFER_SIZE);
	}
	else
		line = ft_gnl_r_rec(fd, save_buffer, line_len + GNL_BUFFER_SIZE);
	if (line == NULL)
		return (NULL);
	ft_memcpy(line + line_len, read_buffer, read_ret);
	return (line);
}
