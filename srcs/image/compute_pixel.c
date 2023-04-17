/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:32:49 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/17 16:14:59 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	do_intersections(t_all *all, t_intersect_ret *res, t_ray *ray);

void	compute_pixel(t_all *all, t_intersect_ret *res, int x, int y)
{
	if (all->show_menu == true && x > (WIDTH - 420) / all->scene.ppr)
		return ;
	init_intersect_ret(res);
	do_intersections(all, res, &all->ray_tab[y][x]);
	if (res->dst != -1.0f)
		compute_light(all, res, &all->ray_tab[y][x], MAX_REFLECT);
	draw_result(all, res, x, y);
}

static void	do_intersections(t_all *all, t_intersect_ret *res, t_ray *ray)
{
	t_rtlst	*obj;

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
}
