/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:08:01 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/17 16:05:45 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include <stdbool.h>

#include "libft.h"

static t_result	add_sphere(t_scene *ret_scene, t_sphere sphere);

t_result	parse_sphere(t_scene *ret_scene)
{
	t_sphere	sphere;
	char		*tok;
	float		radius;
	t_color		color;
	t_vec3	pos;

	tok = ft_strtok(NULL, " \n");
	if (parse_vec(tok, &pos) == FAILURE)
		return (FAILURE);
	tok = ft_strtok(NULL, " \n");
	if (parse_float(tok, &radius) == FAILURE)
		return (FAILURE);
	tok = ft_strtok(NULL, " \n");
	if (parse_color(tok, &color) == FAILURE)
		return (FAILURE);
	if (ft_strtok(NULL, " \n") != NULL)
		return (FAILURE);
	sphere = create_sphere(pos, radius, color);
	if (add_sphere(ret_scene, sphere) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static t_result	add_sphere(t_scene *ret_scene, t_sphere sphere)
{
	t_rtlst	*obj;
	int		nb_obj;

	nb_obj = 0;
	obj = ret_scene->objects;
	while (obj)
	{
		nb_obj++;
		obj = obj->next;
	}
	sphere.id = nb_obj;
	obj = rtlst_new(SPHERE, (t_rtlst_v)sphere, nb_obj);
	if (obj == NULL)
		return (FAILURE);
	rtlst_add_back(&ret_scene->objects, obj);
	return (SUCCESS);
}
