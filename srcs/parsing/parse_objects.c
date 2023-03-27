/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:31:30 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/27 18:08:27 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include <stdbool.h>

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
