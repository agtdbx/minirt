/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:58:42 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/19 13:01:18 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	do_intersections(t_all *all, t_intersect_ret *res, t_ray *ray)
{
	t_rtlst		*obj;
	t_light		*tmp_light;
	t_sphere	sphere;

	obj = all->scene.objects;
	while (obj)
	{
		if (obj->type == SPHERE)
			intersect_sphere(&obj->value.as_sphere, ray, res);
		else if (obj->type == PLANE)
			intersect_plane(&obj->value.as_plane, ray, res);
		else if (obj->type == CYLINDER)
			intersect_cylinder(&obj->value.as_cylinder, ray,
				res);
		obj = obj->next;
	}
	if (all->show_menu)
	{
		tmp_light = all->scene.lights;
		while (tmp_light)
		{
			sphere = create_sphere_from_light(tmp_light);
			intersect_sphere(&sphere, ray, res);
			tmp_light = tmp_light->next;
		}
	}
}

void	do_intersections_without_id(t_all *all, t_intersect_ret *res,
				t_ray *ray, int id_ignore)
{
	t_rtlst	*obj;

	obj = all->scene.objects;
	while (obj)
	{
		if (obj->id != id_ignore)
		{
			if (obj->type == SPHERE)
				intersect_sphere(&obj->value.as_sphere, ray, res);
			else if (obj->type == PLANE)
				intersect_plane(&obj->value.as_plane, ray, res);
			else if (obj->type == CYLINDER)
				intersect_cylinder(&obj->value.as_cylinder, ray,
					res);
		}
		obj = obj->next;
	}
}
