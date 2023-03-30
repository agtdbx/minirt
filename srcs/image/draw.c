/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:29:09 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/30 17:15:02 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	do_intersections(t_all *all, t_dst_and_nrm *res, int x, int y);
static void	draw_pixels(t_all *all, int x, int y, int color);
static void	draw_result(t_all *all, t_dst_and_nrm *res, int x, int y);

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

void	draw(t_all *all)
{
	const int		number_ray = WIDTH / all->scene.ppr;
	const int		number_line = HEIGHT / all->scene.ppr;
	int				x;
	int				y;
	t_dst_and_nrm	res;

	fill_tab_ray(all->ray_tab, &all->scene, number_ray, number_line);
	y = 0;
	while (y < number_line)
	{
		x = 0;
		while (x < number_ray)
		{
			res.dst = -1.0f;
			fill_vec(&res.nrm, 0.0f, 0.0f, 0.0f);
			res.color.r = 0;
			res.color.g = 0;
			res.color.b = 0;
			res.intensity_r = 0.0f;
			res.intensity_g = 0.0f;
			res.intensity_b = 0.0f;
			do_intersections(all, &res, x, y);
			apply_dymamic_light(all, &res, &all->ray_tab[y][x]);
			apply_ambiant_light(all, &res);
			draw_result(all, &res, x, y);
			x++;
		}
		y++;
	}
	apply_antialiasing(all);
}

static void	do_intersections(t_all *all, t_dst_and_nrm *res, int x, int y)
{
	t_rtlst	*obj;

	obj = all->scene.objects;
	while (obj)
	{
		if (obj->type == SPHERE)
			intersect_sphere(&obj->value.as_sphere, &all->ray_tab[y][x], res);
		else if (obj->type == PLANE)
			intersect_plane(&obj->value.as_plane, &all->ray_tab[y][x], res);
		else if (obj->type == CYLINDER)
			intersect_cylinder(&obj->value.as_cylinder, &all->ray_tab[y][x],
				res);
		obj = obj->next;
	}
}

static void	draw_pixels(t_all *all, int x, int y, int color)
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

static void	draw_result(t_all *all, t_dst_and_nrm *res, int x, int y)
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
