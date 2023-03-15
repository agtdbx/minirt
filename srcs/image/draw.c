/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:29:09 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/15 13:12:30 by aderouba         ###   ########.fr       */
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


void	draw(t_scene *scene, t_all *all, int size)
{
	const int	number_ray = WIDTH / size;
	const int	number_line = HEIGHT / size;
	t_ray		**ray_tab;
	int			i;

	// Allocation du tableau de rayons
	ray_tab = malloc(sizeof(t_ray *) * number_line);
	if (ray_tab == NULL)
		return ;
	i = 0;
	while (i < number_line)
	{
		ray_tab[i] = malloc(sizeof(t_ray) * number_ray);
		if (ray_tab[i] == NULL)
		{
			free_ray_tab(ray_tab, i);
			return ;
		}
		i++;
	}
	// Replissage du tableau de rayons
	fill_tab_ray(ray_tab, &scene->camera, number_ray, number_line);

	// Faire les calcules d'intersections ici

	// Dessiner les pixels ici
	(void)all;

	free_ray_tab(ray_tab, number_line);
}

/*
Draw version sans alloc. Comme on peut pas avoir une taille en dessous de 1,
on peut juste avoir un tableau static de taille max.
*/
/*
void	draw(t_scene *scene, t_all *all, int size)
{
	const int	number_ray = WIDTH / size;
	const int	number_line = HEIGHT / size;
	t_ray		ray_tab[HEIGHT][WIDTH];

	// Replissage du tableau de rayons
	fill_tab_ray(ray_tab, &scene->camera, number_ray, number_line);

	// Faire les calcules d'intersections ici

	// Dessiner les pixels ici
	(void)all;
}
*/
