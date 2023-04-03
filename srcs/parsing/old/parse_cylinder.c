/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:31:30 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/28 13:01:22 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_result	add_cylinder(t_scene *ret_scene, t_cylinder cylinder);

t_result	parse_cylinder(t_scene *ret_scene)
{
	t_cylinder	cylinder;
	char		*tok;
	float		param[2];
	t_color		color;

	tok = ft_strtok(NULL, " \n");
	if (parse_vec(tok, &cylinder.origin) == FAILURE)
		return (FAILURE);
	tok = ft_strtok(NULL, " \n");
	if (parse_direction(tok, &cylinder.axis) == FAILURE)
		return (FAILURE);
	tok = ft_strtok(NULL, " \n");
	if (parse_float(tok, &param[0]) == FAILURE)
		return (FAILURE);
	tok = ft_strtok(NULL, " \n");
	if (parse_float(tok, &param[1]) == FAILURE)
		return (FAILURE);
	tok = ft_strtok(NULL, " \n");
	if (parse_color(tok, &color) == FAILURE)
		return (FAILURE);
	if (ft_strtok(NULL, " \n") != NULL)
		return (FAILURE);
	cylinder = create_cylinder(cylinder.origin, cylinder.axis, param, color);
	if (add_cylinder(ret_scene, cylinder) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static t_result	add_cylinder(t_scene *ret_scene, t_cylinder cylinder)
{
	t_rtlst		*obj;

	obj = rtlst_new(CYLINDER, (t_rtlst_v)cylinder);
	if (obj == NULL)
		return (FAILURE);
	rtlst_add_back(&ret_scene->objects, obj);
	return (SUCCESS);
}
