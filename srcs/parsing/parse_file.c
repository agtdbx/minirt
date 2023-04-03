/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:33:27 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/03 17:49:08 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include "main.h"
#include "libft.h"

////////////////////////////////////////////////////////////////////////////////

t_parsing_error			parse_file(
							char const *filename,
							t_scene *ret_scene);

static t_parsing_error	loc_parse_lines(
							int fd,
							char const *filename,
							t_scene *ret_scene);

////////////////////////////////////////////////////////////////////////////////

/** parse_file
 *   parse *.rt file into t_scene object.
 */
t_parsing_error	parse_file(
					char const *filename,
					t_scene *ret_scene)
{
	int				fd;
	t_parsing_error	err;

	if (ft_strlen(filename) <= 3 || !ft_strendswith(filename, ".rt"))
	{
		ft_printf_fd("Error\n", STDERR_FILENO);
		ft_printf_fd("Invalid file name `%s'\n", STDERR_FILENO, filename);
		return (PARSING_ERROR);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		perror(filename);
		return (PARSING_ERROR);
	}
	err = loc_parse_lines(fd, filename, ret_scene);
	close(fd);
	return (err);
}

static t_parsing_error	loc_parse_lines(
							int fd,
							char const *filename,
							t_scene *ret_scene)
{
	char			*line;
	size_t			line_no;
	char			gnl_save_buffer[GNL_BUFFER_SIZE];
	t_parsing_error	err;

	err = PARSING_SUCCESS;
	gnl_save_buffer[0] = '\0';
	line_no = 0;
	while (err != PARSING_ERROR)
	{
		errno = 0;
		line = ft_gnl_r(fd, gnl_save_buffer);
		if (line == NULL && errno != 0)
		{
			ft_putstr_fd("Error\n", STDERR_FILENO);
			perror(filename);
			return (PARSING_ERROR);
		}
		if (line == NULL)
			return (PARSING_SUCCESS);
		err = parse_directive(line_no, filename, line, ret_scene);
		ft_memdel(&line);
		line_no++;
	}
	return (PARSING_ERROR);
}
