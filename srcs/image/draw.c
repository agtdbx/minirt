/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:29:09 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/17 17:02:49 by aderouba         ###   ########.fr       */
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

static void	free_ray_tab(t_ray **ray_tab, int max_alloc)
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


void	draw(t_all *all, int size)
{
	const int		number_ray = WIDTH / size;
	const int		number_line = HEIGHT / size;
	t_ray			**ray_tab;
	int				x;
	int				y;
	float			intensity;
	int				color;
	t_dst_and_nrm	res;
	t_rtlst			*obj;

	// Allocation du tableau de rayons
	ray_tab = malloc(sizeof(t_ray *) * number_line);
	if (ray_tab == NULL)
		return ;
	y = 0;
	while (y < number_line)
	{
		ray_tab[y] = malloc(sizeof(t_ray) * number_ray);
		if (ray_tab[y] == NULL)
		{
			free_ray_tab(ray_tab, y);
			return ;
		}
		y++;
	}

	// Replissage du tableau de rayons
	fill_tab_ray(ray_tab, &all->scene.camera, number_ray, number_line);

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
					intersect_sphere(&obj->value.as_sphere, &ray_tab[y][x], &res);
				else if (obj->type == PLANE)
					intersect_plane(&obj->value.as_plane, &ray_tab[y][x], &res);
				else if (obj->type == CYLINDER)
					intersect_cylinder(&obj->value.as_cylinder, &ray_tab[y][x], &res);
				obj = obj->next;
			}

			if (res.dst != -1.0f)
			{
				res.nrm = create_vector(res.nrm.x, res.nrm.y, res.nrm.z, true);
				ray_tab[y][x].direction = create_vector(ray_tab[y][x].direction.x, ray_tab[y][x].direction.y, ray_tab[y][x].direction.z, true);
				intensity = (-dot_product(&res.nrm, &ray_tab[y][x].direction)) * 255;
				color = intensity;
				mlx_put_pixel(all->img, x, y, get_rgb(color, color, color));
			}
			else
				mlx_put_pixel(all->img, x, y, 0x000000FF);
				
			x++;
		}
		y++;
	}
	// Dessiner les pixels ici
	mlx_image_to_window(all->mlx, all->img, 0, 0);

	free_ray_tab(ray_tab, number_line);
}