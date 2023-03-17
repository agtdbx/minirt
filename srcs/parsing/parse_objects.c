/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:31:30 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/17 16:12:48 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	parse_camera(t_scene *scene)
{
	char		*part;
	float		vect[3];
	float		len;
	t_vector	basis[2];

	if (scene->camera.fov != 0)
		return (false);
	part = ft_strtok(NULL, " \n");
	if (!parse_vector(part, vect, 0.0f, 0.0f))
		return (false);
	scene->camera.pos = create_vector(vect[0], vect[1], vect[2], false);
	part = ft_strtok(NULL, " \n");
	if (!parse_vector(part, vect, -1.0f, 1.0f))
		return (false);
	scene->camera.basis[2] = create_vector(vect[0], vect[1], vect[2], true);
	part = ft_strtok(NULL, " \n");
	if (!is_int(part))
		return (false);
	scene->camera.fov = ft_atoi(part);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		return (false);
	part = ft_strtok(NULL, " \n");
	len = WIDTH / (tan(scene->camera.fov * PI_DIV_360) * 2.0f);
	scene->camera.orientation = multiply_vect_number(&scene->camera.basis[2], len);
	get_screen_basis(&scene->camera.basis[2], basis, 1);
	scene->camera.basis[0] = create_vector(basis[0].x, basis[0].y, basis[0].z,
								true);
	scene->camera.basis[1] = create_vector(basis[1].x, basis[1].y, basis[1].z,
								true);
	return (part == NULL);
}

bool	parse_sphere(t_scene *scene)
{
	t_sphere	sphere;
	t_rtlst		*obj;
	char		*part;
	float		vect[3];
	t_vector	pos;
	float		radius;
	int			color;

	part = ft_strtok(NULL, " \n");
	if (!parse_vector(part, vect, 0.0f, 0.0f))
		return (false);
	pos = create_vector(vect[0], vect[1], vect[2], false);
	part = ft_strtok(NULL, " \n");
	if (!is_float(part))
		return (false);
	radius = ft_atof(part);
	part = ft_strtok(NULL, " \n");
	color = parse_color(part);
	if (color == 0)
		return (false);
	if (ft_strtok(NULL, " \n") != NULL)
		return (false);
	sphere = create_sphere(pos, radius, color);
	obj = rtlst_new(SPHERE, (t_rtlst_v)sphere);
	if (obj == NULL)
		return (false);
	rtlst_add_back(&scene->objects, obj);
	return (true);
}

bool	parse_plane(t_scene *scene)
{
	t_plane		plane;
	t_rtlst		*obj;
	char		*part;
	float		vect[3];
	t_vector	pos;
	t_vector	nrm;
	int			color;

	part = ft_strtok(NULL, " \n");
	if (!parse_vector(part, vect, 0.0f, 0.0f))
		return (false);
	pos = create_vector(vect[0], vect[1], vect[2], false);
	part = ft_strtok(NULL, " \n");
	if (!parse_vector(part, vect, -1.0f, 1.0f))
		return (false);
	nrm = create_vector(vect[0], vect[1], vect[2], true);
	part = ft_strtok(NULL, " \n");
	color = parse_color(part);
	if (color == 0)
		return (false);
	if (ft_strtok(NULL, " \n") != NULL)
		return (false);
	plane = create_plane(pos, nrm, color);
	obj = rtlst_new(PLANE, (t_rtlst_v)plane);
	if (obj == NULL)
		return (false);
	rtlst_add_back(&scene->objects, obj);
	return (true);
}

bool	parse_cylinder(t_scene *scene)
{
	t_cylinder	cylinder;
	t_rtlst		*obj;
	char		*part;
	float		vect[3];
	t_vector	pos;
	t_vector	axis;
	float		param[2];
	int			color;

	part = ft_strtok(NULL, " \n");
	if (part == NULL)
		return (false);
	if (!parse_vector(part, vect, 0.0f, 0.0f))
		return (false);
	pos = create_vector(vect[0], vect[1], vect[2], false);
	part = ft_strtok(NULL, " \n");
	if (part == NULL)
		return (false);
	if (!parse_vector(part, vect, -1.0f, 1.0f))
		return (false);
	axis = create_vector(vect[0], vect[1], vect[2], true);
	part = ft_strtok(NULL, " \n");
	if (part == NULL)
		return (false);
	if (!is_float(part))
		return (false);
	param[0] = ft_atof(part);
	part = ft_strtok(NULL, " \n");
	if (part == NULL)
		return (false);
	if (!is_float(part))
		return (false);
	param[1] = ft_atof(part);
	part = ft_strtok(NULL, " \n");
	if (part == NULL)
		return (false);
	color = parse_color(part);
	if (color == 0)
		return (false);
	if (ft_strtok(NULL, " \n") != NULL)
		return (false);
	cylinder = create_cylinder(pos, axis, param, color);
	obj = rtlst_new(CYLINDER, (t_rtlst_v)cylinder);
	if (obj == NULL)
		return (false);
	rtlst_add_back(&scene->objects, obj);
	return (true);
}
