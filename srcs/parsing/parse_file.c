/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 09:53:06 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/27 18:51:55 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include <unistd.h>

#include "libft.h"

static t_result	parse_lines(int fd, t_scene *ret_scene);
static t_result	parse_line(char const *identifier, t_scene *ret_scene);

t_result	parse_file(char const *filename, t_scene *ret_scene)
{
	int	fd;

	*ret_scene = (t_scene){0};
	if (ft_strlen(filename) <= 3 || !ft_strendswith(filename, ".rt"))
	{
		ft_printf_fd("Error\n", STDERR_FILENO);
		ft_printf_fd("Invalid file name `%s'\n", STDERR_FILENO, filename);
		return (FAILURE);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_printf_fd("Error\n", STDERR_FILENO);
		ft_printf_fd("Couldn't open `%s'\n", STDERR_FILENO, filename);
		return (FAILURE);
	}
	if (parse_lines(fd, ret_scene) == FAILURE)
	{
		close(fd);
		rtlst_free(&ret_scene->objects);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

static t_result	parse_lines(int fd, t_scene *ret_scene)
{
	char	*line;
	char	*identifier;

	line = get_next_line(fd);
	while (line != NULL)
	{
		identifier = ft_strtok(line, " ");
		if (parse_line(identifier, ret_scene) == FAILURE)
		{
			free(line);
			return (FAILURE);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (SUCCESS);
}

static t_result	parse_line(char const *identifier, t_scene *ret_scene)
{
	if (ft_strcmp("A", identifier) == 0)
		return (parse_ambient_light(ret_scene));
	else if (ft_strcmp("C", identifier) == 0)
		return (parse_camera(ret_scene));
	else if (ft_strcmp("L", identifier) == 0)
		return (parse_light(ret_scene));
	else if (ft_strcmp("sp", identifier) == 0)
		return (parse_sphere(ret_scene));
	else if (ft_strcmp("pl", identifier) == 0)
		return (parse_plane(ret_scene));
	else if (ft_strcmp("cy", identifier) == 0)
		return (parse_cylinder(ret_scene));
	else if (ft_strcmp("\n", identifier) == 0)
		return (SUCCESS);
	ft_printf_fd("Error\n", STDERR_FILENO);
	ft_printf_fd("Unexpected identifier `%s'\n", STDERR_FILENO, identifier);
	return (FAILURE);
}
