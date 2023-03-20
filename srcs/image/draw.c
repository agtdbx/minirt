/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:29:09 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/20 17:30:19 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	get_rgb(int r, int g, int b)
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

void	free_ray_tab(t_ray **ray_tab, int max_alloc)
{
	int	i;

	i = 0;
	while (i < max_alloc)
	{
		free(ray_tab[i]);
		i++;
	}
	free(ray_tab);
}


t_ray	**alloc_ray_tab(void)
{
	int		y;
	t_ray	**ray_tab;

	ray_tab = malloc(sizeof(t_ray *) * HEIGHT);
	if (ray_tab == NULL)
		return (NULL);
	y = 0;
	while (y < HEIGHT)
	{
		ray_tab[y] = malloc(sizeof(t_ray) * WIDTH);
		if (ray_tab[y] == NULL)
		{
			free_ray_tab(ray_tab, y);
			return (NULL);
		}
		y++;
	}
	return (ray_tab);
}


static void	draw_pixels(t_all *all, int x, int y, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < all->draw_size)
	{
		i = 0;
		while (i < all->draw_size)
		{
			mlx_put_pixel(all->img, (x * all->draw_size) + i, (y * all->draw_size) + j, color);
			i++;
		}
		j++;
	}
}


void	draw(t_all *all)
{
	const int		number_ray = WIDTH / all->draw_size;
	const int		number_line = HEIGHT / all->draw_size;
	int				x;
	int				y;
	float			intensity;
	int				color;
	int				r, g, b;
	t_dst_and_nrm	res;
	t_rtlst			*obj;

	// Replissage du tableau de rayons
	fill_tab_ray(all->ray_tab, &all->scene.camera, number_ray, number_line);

	// Faire les calcules d'intersections ici
	y = 0;
	while (y < number_line)
	{
		x = 0;
		while (x < number_ray)
		{
			res.dst = -1.0f;
			res.nrm = create_vector(0.0f, 0.0f, 0.0f, false);

			obj = all->scene.objects;
			while (obj)
			{
				if (obj->type == SPHERE)
					intersect_sphere(&obj->value.as_sphere, &all->ray_tab[y][x], &res);
				else if (obj->type == PLANE)
					intersect_plane(&obj->value.as_plane, &all->ray_tab[y][x], &res);
				else if (obj->type == CYLINDER)
					intersect_cylinder(&obj->value.as_cylinder, &all->ray_tab[y][x], &res);
				obj = obj->next;
			}

			if (res.dst != -1.0f)
			{
				res.nrm = create_vector(res.nrm.x, res.nrm.y, res.nrm.z, true);
				all->ray_tab[y][x].direction = create_vector(all->ray_tab[y][x].direction.x, all->ray_tab[y][x].direction.y, all->ray_tab[y][x].direction.z, true);
				intensity = (-dot_product(&res.nrm, &all->ray_tab[y][x].direction)) * 255;
				color = intensity;
				all->colors_tab[y][x] = get_rgb(color, color, color);
			}
			else
				all->colors_tab[y][x] = 0x000000FF;

			x++;
		}
		y++;
	}

	y = 0;
	while (y < number_line)
	{
		x = 0;
		while (x < number_ray)
		{
			// Antialiasing
			if (x > 1 && x < number_ray - 1 && y > 1 && y < number_line - 1)
			{
				r = all->colors_tab[y - 1][x - 1] >> 24 & 0xFF;
				g = all->colors_tab[y - 1][x - 1] >> 16 & 0xFF;
				b = all->colors_tab[y - 1][x - 1] >> 8 & 0xFF;

				r += all->colors_tab[y - 1][x] >> 24 & 0xFF;
				g += all->colors_tab[y - 1][x] >> 16 & 0xFF;
				b += all->colors_tab[y - 1][x] >> 8 & 0xFF;

				r += all->colors_tab[y - 1][x + 1] >> 24 & 0xFF;
				g += all->colors_tab[y - 1][x + 1] >> 16 & 0xFF;
				b += all->colors_tab[y - 1][x + 1] >> 8 & 0xFF;

				r += all->colors_tab[y][x - 1] >> 24 & 0xFF;
				g += all->colors_tab[y][x - 1] >> 16 & 0xFF;
				b += all->colors_tab[y][x - 1] >> 8 & 0xFF;

				r += all->colors_tab[y][x + 1] >> 24 & 0xFF;
				g += all->colors_tab[y][x + 1] >> 16 & 0xFF;
				b += all->colors_tab[y][x + 1] >> 8 & 0xFF;

				r += all->colors_tab[y + 1][x - 1] >> 24 & 0xFF;
				g += all->colors_tab[y + 1][x - 1] >> 16 & 0xFF;
				b += all->colors_tab[y + 1][x - 1] >> 8 & 0xFF;

				r += all->colors_tab[y + 1][x] >> 24 & 0xFF;
				g += all->colors_tab[y + 1][x] >> 16 & 0xFF;
				b += all->colors_tab[y + 1][x] >> 8 & 0xFF;

				r += all->colors_tab[y + 1][x] >> 24 & 0xFF;
				g += all->colors_tab[y + 1][x] >> 16 & 0xFF;
				b += all->colors_tab[y + 1][x] >> 8 & 0xFF;

				r >>= 3;
				g >>= 3;
				b >>= 3;

				color = get_rgb(r, g, b);
			}
			else
				color = all->colors_tab[y][x];
			draw_pixels(all, x, y, color);
			x++;
		}
		y++;
	}
}
