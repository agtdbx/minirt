/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:31:30 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/19 15:12:21 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_result	add_cone(t_scene *ret_scene, t_cone cone);

t_result	parse_cone(t_scene *ret_scene)
{
	t_cone	cone;
	char	*tok;
	float	param[2];
	t_color	color;

	tok = ft_strtok(NULL, " \n");
	if (parse_vec(tok, &cone.origin) == FAILURE)
		return (FAILURE);
	tok = ft_strtok(NULL, " \n");
	if (parse_direction(tok, &cone.axis) == FAILURE)
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
	cone = create_cone(cone.origin, cone.axis, param, color);
	if (add_cone(ret_scene, cone) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static t_result	add_cone(t_scene *ret_scene, t_cone cone)
{
	t_rtlst		*obj;
	int		nb_obj;

	nb_obj = 0;
	obj = ret_scene->objects;
	while (obj)
	{
		nb_obj++;
		obj = obj->next;
	}
	cone.id = nb_obj;
	obj = rtlst_new(CONE, (t_rtlst_v)cone, nb_obj);
	if (obj == NULL)
		return (FAILURE);
	rtlst_add_back(&ret_scene->objects, obj);
	return (SUCCESS);
}
