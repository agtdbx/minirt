/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:39:21 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/15 12:14:18 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_vector	dup_vect(t_vector *vector)
{
	t_vector	new;

	new.x = vector->x;
	new.y = vector->y;
	new.z = vector->z;
	return (new);
}

/*
Take a static list of ray and the number of ray
Take the camera and the size of ray (How many pixel are trace per ray)
*/
void	fov_to_ray_list(t_ray *ray_lst, t_camera *camera, int number_ray)
{
	const float	angle_per_ray = camera->fov / number_ray;
	int			i;
	t_vector	to_decale;
	t_vector	tmp;

	// Je récupère le décalage vers la gauche
	tmp = dup_vect(&camera->orientation);
	rotate(&tmp, -angle_per_ray, ROTATE_AROUND_Y);
	to_decale = sub_vect_vect(&tmp, &camera->orientation);
	// Boucle pour créer les rayons de gauche
	i = number_ray / 2;
	ray_lst[i].origin = dup_vect(&camera->pos);
	ray_lst[i].direction = dup_vect(&camera->orientation);
	i--;
	while (i >= 0)
	{
		ray_lst[i].origin = dup_vect(&camera->pos);
		ray_lst[i].direction = add_vect_vect(&ray_lst[i + 1].direction, &to_decale);
		i--;
	}
	// Je récupère le décalage vers la droite
	tmp = dup_vect(&camera->orientation);
	rotate(&tmp, angle_per_ray, ROTATE_AROUND_Y);
	to_decale = sub_vect_vect(&tmp, &camera->orientation);
	// Boucle pour créer les rayons de droite
	i = number_ray / 2;
	i++;
	while (i < number_ray)
	{
		ray_lst[i].origin = dup_vect(&camera->pos);
		ray_lst[i].direction = add_vect_vect(&ray_lst[i - 1].direction, &to_decale);
		i++;
	}
}

/*
Take a static tab of ray.
The number of ray per line is the width of the window / size
The number of line is the height of the window / size
Take the camera and the size of ray (How many pixel are trace per ray)
*/
void	fill_tab_ray(t_ray **ray_tab, t_camera *camera,
			int number_ray, int number_line)
{
	const int	height_per_ray = HEIGHT / number_line;
	int			x;
	int			y;

	// On créer la ligne de rayon au milieu de l'écran
	y = number_line / 2;
	fov_to_ray_list(ray_tab[y], camera, number_ray);
	// On va set les lignes au dessus de celle du milieu
	y--;
	while (y >= 0)
	{
		x = 0;
		while (x < number_ray)
		{
			// Pour chaque rayon, on dup la direction
			ray_tab[y][x].direction = dup_vect(&ray_tab[y + 1][x].direction);
			// On dup aussi l'origine
			ray_tab[y][x].origin = dup_vect(&ray_tab[y + 1][x].origin);
			// Puis on augmente le y
			ray_tab[y][x].origin.y += height_per_ray;
			x++;
		}
		y--;
	}
	// On va set les lignes en dessous de celle du milieu
	y = number_line / 2;
	y++;
	while (y < number_line)
	{
		x = 0;
		while (x < number_ray)
		{
			// Pour chaque rayon, on dup la direction
			ray_tab[y][x].direction = dup_vect(&ray_tab[y + 1][x].direction);
			// On dup aussi l'origine
			ray_tab[y][x].origin = dup_vect(&ray_tab[y + 1][x].origin);
			// Puis on baisse le y
			ray_tab[y][x].origin.y -= height_per_ray;
			x++;
		}
		y++;
	}
}
