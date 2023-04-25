/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:32:49 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/25 18:06:44 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
