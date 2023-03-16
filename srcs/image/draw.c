/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:29:09 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/16 16:26:28 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
	t_dst_and_nrm	res;
	t_rtlst			*obj;

	printf("ALLOCATE RAY TAB\n");
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

	printf("FILL RAY TAB\n");
	// Replissage du tableau de rayons
	fill_tab_ray(ray_tab, &all->scene.camera, number_ray, number_line);


	printf("CALCULATE IMAGE\n");
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
				mlx_put_pixel(all->img, x, y, 0xFFFFFFFF);
			else
				mlx_put_pixel(all->img, x, y, 0x000000FF);
				
			x++;
		}
		y++;
	}

	printf("PUT IMAGE\n");
	// Dessiner les pixels ici
	mlx_image_to_window(all->mlx, all->img, 0, 0);

	free_ray_tab(ray_tab, number_line);

	printf("DONE\n");
}