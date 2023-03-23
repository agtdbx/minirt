/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:29:09 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/23 11:06:22 by aderouba         ###   ########.fr       */
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
			res.color = 0x000000FF;
			do_intersections(all, &res, x, y);
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
	int			r;
	int			g;
	int			b;
	float		intensity;
	t_vector	tmp;

	if (res->dst != -1.0f)
	{
		fill_vec(&res->nrm, res->nrm.x, res->nrm.y, res->nrm.z);
		fill_vec(&tmp, all->ray_tab[y][x].direction.x,
				all->ray_tab[y][x].direction.y,
				all->ray_tab[y][x].direction.z);
		normalize_vec(&res->nrm);
		normalize_vec(&tmp);
		all->ray_tab[y][x].direction = tmp;
		intensity = -dot_product(&res->nrm, &all->ray_tab[y][x].direction);
		intensity *= all->scene.al_intensity;
		r = (res->color >> 24 & 0XFF) * intensity;
		g = (res->color >> 16 & 0XFF) * intensity;
		b = (res->color >> 8 & 0XFF) * intensity;
		r *= ((all->scene.al_color >> 24 & 0XFF) / 255.0f);
		g *= ((all->scene.al_color >> 16 & 0XFF) / 255.0f);
		b *= ((all->scene.al_color >> 8 & 0XFF) / 255.0f);
		draw_pixels(all, x, y, get_rgb(r, g, b));
	}
	else
		draw_pixels(all, x, y, 0x000000FF);
}
