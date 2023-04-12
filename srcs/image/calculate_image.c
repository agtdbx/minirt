/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_image.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:52:58 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/12 12:48:26 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	compute_pixel(t_all *all, t_intersect_ret *res, int x, int y);

void	calculate_image(t_all *all)
{
	const int		number_ray = WIDTH / all->scene.ppr;
	const int		number_line = HEIGHT / all->scene.ppr;
	int				x;
	int				y;
	t_intersect_ret	res;

	fill_tab_ray(all->ray_tab, &all->scene, number_ray, number_line);
	y = 0;
	while (y < number_line)
	{
		x = 0;
		while (x < number_ray)
		{
			compute_pixel(all, &res, x, y);
			if (all->mouse.pressed
				&& all->mouse.tab_x == x && all->mouse.tab_y == y)
			{
				all->menu.id_obj_select = res.id;
				all->draw_state = NEED_REDRAW;
			}
			x++;
		}
		y++;
	}
	apply_antialiasing(all);
}

static void	compute_pixel(t_all *all, t_intersect_ret *res, int x, int y)
{
	if (all->show_menu == true && x > (WIDTH - 420) / all->scene.ppr)
		return ;
	init_intersect_ret(res);
	do_intersections(all, res, &all->ray_tab[y][x]);
	if (res->dst != -1.0f)
		compute_light(all, res, &all->ray_tab[y][x], MAX_REFLECT);
	draw_result(all, res, x, y);
}

void	do_intersections(t_all *all, t_intersect_ret *res, t_ray *ray)
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


