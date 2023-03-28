/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:16:00 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/28 12:33:32 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_result	add_plane(t_scene *ret_scene, t_plane plane);

t_result	parse_plane(t_scene *ret_scene)
{
	t_plane		plane;
	char		*tok;
	t_vector	pos;
	t_vector	nrm;
	t_color		color;

	tok = ft_strtok(NULL, " \n");
	if (parse_vec(tok, &pos) == FAILURE)
		return (FAILURE);
	tok = ft_strtok(NULL, " \n");
	if (parse_direction(tok, &nrm) == FAILURE)
		return (FAILURE);
	tok = ft_strtok(NULL, " \n");
	if (parse_color(tok, &color) == FAILURE)
		return (FAILURE);
	if (ft_strtok(NULL, " \n") != NULL)
		return (FAILURE);
	plane = create_plane(pos, nrm, color);
	if (add_plane(ret_scene, plane) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static t_result	add_plane(t_scene *ret_scene, t_plane plane)
{
	t_rtlst		*obj;

	obj = rtlst_new(PLANE, (t_rtlst_v)plane);
	if (obj == NULL)
		return (FAILURE);
	rtlst_add_back(&ret_scene->objects, obj);
	return (SUCCESS);
}
