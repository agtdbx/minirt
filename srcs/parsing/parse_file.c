/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 09:53:06 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/02 11:48:20 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_scene	init_scene(void);
static bool		check_filename(char *filename);
static bool		read_file(int fd, t_scene *scene);

// Met res.al_intensity à -1 en cas de pb et print le message d'erreur
// Sinon récup les infos dans le fichers
t_scene	parse_file(char *filename)
{
	t_scene	res;
	int		fd;

	res = init_scene();
	if (!check_filename(filename))
		return (res);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_printf_fd("'%s' can be find or open\n", 2, filename);
		return (res);
	}
	if (!read_file(fd, &res))
		res.al_intensity = -1.0f;
	return (res);
}

static t_scene	init_scene(void)
{
	t_scene	res;

	res.al_intensity = -1.0f;
	res.al_color = 0;
	res.camera.pos = create_vector(0.0f, 0.0f, 0.0f, false);
	res.camera.orientation = create_vector(0.0f, 0.0f, 0.0f, false);
	res.camera.fov = 0;
	res.light.pos = create_vector(0.0f, 0.0f, 0.0f, false);
	res.light.brightness = -1.0f;
	res.light.color = 0;
	res.objects = NULL;
	return (res);
}

static bool	check_filename(char *filename)
{
	int		i;
	bool	res;

	i = ft_strlen(filename);
	res = true;
	if (i <= 3)
		res = false;
	else if (filename[i - 1] != 't')
		res = false;
	else if (filename[i - 2] != 'r')
		res = false;
	else if (filename[i - 3] != '.')
		res = false;
	if (!res)
		ft_printf_fd("'%s' is not a file for minirt\n", 2, filename);
	return (res);
}

static bool	read_file(int fd, t_scene *scene)
{
	bool	parse_ok;
	char	*line;
	char	*word;

	parse_ok = true;
	line = get_next_line(fd);
	while (line && parse_ok)
	{
		word = ft_strtok(line, " ");
		if (ft_strcmp(word, "A") == 0)
			parse_ok = parse_ambient_light(scene);
		else if (ft_strcmp(word, "C") == 0)
			parse_ok = parse_camera(scene);
		else if (ft_strcmp(word, "L") == 0)
			parse_ok = parse_light(scene);
		else if (ft_strcmp(word, "sp") == 0)
			parse_ok = parse_sphere(scene);
		else if (ft_strcmp(word, "pl") == 0)
			parse_ok = parse_plane(scene);
		else if (ft_strcmp(word, "cy") == 0)
			parse_ok = parse_cylinder(scene);
		else if (ft_strcmp(line, "\n") != 0)
		{
			ft_printf_fd("Unexpected identifier '%s'\n", 2, line);
			parse_ok = false;
		}
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (parse_ok);
}
