/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:04:55 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/17 16:15:16 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	add_color(int color, int *r, int *g, int *b);
static int	get_merge_color(t_all *all, int x, int y);

void	apply_antialiasing(t_all *all)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (x > 1 && x < WIDTH - 1 && y > 1 && y < HEIGHT - 1)
				color = get_merge_color(all, x, y);
			else
				color = all->colors_tab[y][x];
			mlx_put_pixel(all->img, x, y, color);
			x++;
		}
		y++;
	}
}

static void	add_color(int color, int *r, int *g, int *b)
{
	*r += color >> 24 & 0xFF;
	*g += color >> 16 & 0xFF;
	*b += color >> 8 & 0xFF;
}

static int	get_merge_color(t_all *all, int x, int y)
{
	int	r;
	int	g;
	int	b;

	r = 0;
	g = 0;
	b = 0;
	add_color(all->colors_tab[y - 1][x - 1], &r, &g, &b);
	add_color(all->colors_tab[y - 1][x], &r, &g, &b);
	add_color(all->colors_tab[y - 1][x + 1], &r, &g, &b);
	add_color(all->colors_tab[y][x - 1], &r, &g, &b);
	add_color(all->colors_tab[y][x + 1], &r, &g, &b);
	add_color(all->colors_tab[y + 1][x - 1], &r, &g, &b);
	add_color(all->colors_tab[y + 1][x], &r, &g, &b);
	add_color(all->colors_tab[y + 1][x + 1], &r, &g, &b);
	r >>= 3;
	g >>= 3;
	b >>= 3;
	return (get_rgb(r, g, b));
}
