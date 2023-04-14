/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_image.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:52:58 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/14 11:35:14 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
