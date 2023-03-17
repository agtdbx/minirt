/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:39:21 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/17 14:04:39 by aderouba         ###   ########.fr       */
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

static inline void	vec_fill(float x, float y, float z, t_vector *ret_vec)
{
	ret_vec->x = x;
	ret_vec->y = y;
	ret_vec->z = z;
}

static inline float	vec_getnorm(t_vector const *vec)
{
	return (sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z)));
}

static inline void	vec_scale(float factor, t_vector *ret_vec)
{
	ret_vec->x *= factor;
	ret_vec->y *= factor;
	ret_vec->z *= factor;
}

/** get_screen_basis:
 *   return basis of screen plan(plan normal to camera), such that
 *   ret_basis[0] || Oxz
 *   ret_basis[0] . camera = 0
 *   ret_basis[1] . camera = 0
 */
static void	get_screen_basis(t_vector const *camera, t_vector ret_basis[2], int ppr)
{
	float const	a = camera->x;
	float const	b = camera->y;
	float const	c = camera->z;

	vec_fill(-c, 0.0f, a, &ret_basis[0]);
	vec_scale(ppr / vec_getnorm(&ret_basis[0]), &ret_basis[0]);
	vec_fill(a * b, -(a * a) - (c * c), b * c, &ret_basis[1]);
	vec_scale(ppr / vec_getnorm(&ret_basis[1]), &ret_basis[1]);
}


/*
Take a static list of ray and the number of ray
Take the camera and the size of ray (How many pixel are trace per ray)
*/
static void	fov_to_ray_list(t_ray *ray_lst, t_camera *camera, int number_ray,
			t_vector screen_vect[2])
{
	int	i;
	
	// Boucle pour créer les rayons de gauche
	i = number_ray / 2;
	ray_lst[i].origin = dup_vect(&camera->pos);
	ray_lst[i].direction = dup_vect(&camera->orientation);

	i--;
	while (i >= 0)
	{
		ray_lst[i].origin = dup_vect(&camera->pos);
		ray_lst[i].direction = sub_vect_vect(&ray_lst[i + 1].direction,
								&screen_vect[0]);
		// print_vect(&ray_lst[i].direction);
		i--;
	}
	// Boucle pour créer les rayons de droite
	i = number_ray / 2;
	i++;
	while (i < number_ray)
	{
		ray_lst[i].origin = dup_vect(&camera->pos);
		ray_lst[i].direction = add_vect_vect(&ray_lst[i - 1].direction,
								&screen_vect[0]);
		// print_vect(&ray_lst[i].direction);
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
	// const int	height_per_ray = HEIGHT / number_line;
	int			x;
	int			y;
	t_vector	screen_vect[2];

	get_screen_basis(&camera->orientation, screen_vect, 1);

	print_vect(&camera->orientation);
	print_vect(&screen_vect[0]);
	print_vect(&screen_vect[1]);

	// On créer la ligne de rayon au milieu de l'écran
	y = number_line / 2;
	fov_to_ray_list(ray_tab[y], camera, number_ray, screen_vect);
	// On va set les lignes au dessus de celle du milieu
	y--;
	while (y >= 0)
	{
		x = 0;
		while (x < number_ray)
		{
			// Pour chaque rayon, on dup la direction
			ray_tab[y][x].direction = sub_vect_vect(&ray_tab[y + 1][x].direction,
										&screen_vect[1]);
			// On dup aussi l'origine
			ray_tab[y][x].origin = dup_vect(&ray_tab[y + 1][x].origin);
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
			ray_tab[y][x].direction = add_vect_vect(&ray_tab[y - 1][x].direction,
										&screen_vect[1]);
			// On dup aussi l'origine
			ray_tab[y][x].origin = dup_vect(&ray_tab[y - 1][x].origin);
			x++;
		}
		y++;
	}
}
