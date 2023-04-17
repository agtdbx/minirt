/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:29:09 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/17 16:14:57 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	get_rgb(int r, int g, int b)
{
	if (r < 0)
		r = 0;
	else if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	else if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	else if (b > 255)
		b = 255;
	return (r << 24 | g << 16 | b << 8 | 255);
}

void	draw_pixels(t_all *all, int x, int y, int color)
{
	int	i;
	int	j;
	int	tmp_x;
	int	tmp_y;

	j = 0;
	while (j < all->scene.ppr)
	{
		i = 0;
		while (i < all->scene.ppr)
		{
			tmp_x = (x * all->scene.ppr) + i;
			tmp_y = (y * all->scene.ppr) + j;
			all->colors_tab[tmp_y][tmp_x] = color;
			i++;
		}
		j++;
	}
}

void	draw_result(t_all *all, t_intersect_ret *res, int x, int y)
{
	int	r;
	int	g;
	int	b;

	if (res->dst != -1.0f)
	{
		r = res->color.r * res->intensity_r;
		g = res->color.g * res->intensity_g;
		b = res->color.b * res->intensity_b;
		draw_pixels(all, x, y, get_rgb(r, g, b));
	}
	else
		draw_pixels(all, x, y, 0x000000FF);
}
