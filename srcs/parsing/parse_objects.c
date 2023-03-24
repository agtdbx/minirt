/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:31:30 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/24 14:31:05 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	parse_camera(t_scene *scene)
{
	char		*part;
	float		vect[3];
	float		len;
	t_vector	basis[2];

	if (scene->camera.fov != -1)
		return (false);
	part = ft_strtok(NULL, " \n");
	if (!parse_vector(part, vect, 0.0f, 0.0f))
		return (false);
	fill_vec(&scene->camera.pos, vect[0], vect[1], vect[2]);
	part = ft_strtok(NULL, " \n");
	if (!parse_vector(part, vect, -1.0f, 1.0f))
		return (false);
	fill_vec(&scene->camera.basis[2], vect[0], vect[1], vect[2]);
	normalize_vec(&scene->camera.basis[2]);
	part = ft_strtok(NULL, " \n");
	if (!is_int(part))
		return (false);
	scene->camera.fov = ft_atoi(part);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		return (false);
	part = ft_strtok(NULL, " \n");
	len = WIDTH / (tan(scene->camera.fov * PI_DIV_360) * 2.0f);
	dup_vec(&scene->camera.orientation, &scene->camera.basis[2]);
	multiply_vec_number(&scene->camera.orientation, len);
	get_screen_basis(&scene->camera.basis[2], basis, 1);
	fill_vec(&scene->camera.basis[0], basis[0].x, basis[0].y, basis[0].z);
	fill_vec(&scene->camera.basis[1], basis[1].x, basis[1].y, basis[1].z);
	normalize_vec(&scene->camera.basis[0]);
	normalize_vec(&scene->camera.basis[1]);
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
	fill_vec(&pos, vect[0], vect[1], vect[2]);
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
	fill_vec(&pos, vect[0], vect[1], vect[2]);
	part = ft_strtok(NULL, " \n");
	if (!parse_vector(part, vect, -1.0f, 1.0f))
		return (false);
	fill_vec(&nrm, vect[0], vect[1], vect[2]);
	normalize_vec(&nrm);
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
	fill_vec(&pos, vect[0], vect[1], vect[2]);
	part = ft_strtok(NULL, " \n");
	if (part == NULL)
		return (false);
	if (!parse_vector(part, vect, -1.0f, 1.0f))
		return (false);
	fill_vec(&axis, vect[0], vect[1], vect[2]);
	normalize_vec(&axis);
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
