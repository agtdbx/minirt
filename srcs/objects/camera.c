/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:39:21 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/03 11:13:34 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	fill_ray_tab_top(t_ray **ray_tab, t_vector screen_vect[2],
				int number_ray, int number_line);
static void	fill_ray_tab_bot(t_ray **ray_tab, t_vector screen_vect[2],
				int number_ray, int number_line);
static void	fov_to_ray_list(t_ray *ray_lst, t_camera *camera, int number_ray,
				t_vector screen_vect[2]);

/** get_screen_basis:
 *   return basis of screen plan(plan normal to camera), such that
 *   ret_basis[0] || Oxz
 *   ret_basis[0] . camera = 0
 *   ret_basis[1] . camera = 0
 */
void	get_screen_basis(t_vector const *camera, t_vector ret_basis[2], int ppr)
{
	float const	a = camera->x;
	float const	b = camera->y;
	float const	c = camera->z;

	fill_vec(&ret_basis[0], -c, 0.0f, a);
	multiply_vec_number(&ret_basis[0], ppr / get_length_vec(&ret_basis[0]));
	fill_vec(&ret_basis[1], a * b, -(a * a) - (c * c), b * c);
	multiply_vec_number(&ret_basis[1], ppr / get_length_vec(&ret_basis[1]));
}

/*
Take a static tab of ray.
The number of ray per line is the width of the window / size
The number of line is the height of the window / size
Take the camera and the size of ray (How many pixel are trace per ray)
*/
void	fill_tab_ray(t_ray **ray_tab, t_scene *scene,
			int number_ray, int number_line)
{
	t_vector	screen_vect[2];

	get_screen_basis(&scene->camera.orientation, screen_vect, scene->ppr);
	fov_to_ray_list(ray_tab[number_line / 2], &scene->camera, number_ray,
		screen_vect);
	fill_ray_tab_top(ray_tab, screen_vect, number_ray, number_line);
	fill_ray_tab_bot(ray_tab, screen_vect, number_ray, number_line);
}

/*
Take a static list of ray and the number of ray
Take the camera and the size of ray (How many pixel are trace per ray)
*/
static void	fov_to_ray_list(t_ray *ray_lst, t_camera *camera, int number_ray,
			t_vector screen_vect[2])
{
	int	i;

	i = number_ray / 2;
	dup_vec(&ray_lst[i].origin, &camera->pos);
	dup_vec(&ray_lst[i].direction, &camera->orientation);
	i--;
	while (i >= 0)
	{
		dup_vec(&ray_lst[i].origin, &camera->pos);
		dup_vec(&ray_lst[i].direction, &ray_lst[i + 1].direction);
		sub_vec_vec(&ray_lst[i].direction, &screen_vect[0]);
		i--;
	}
	i = number_ray / 2;
	i++;
	while (i < number_ray)
	{
		dup_vec(&ray_lst[i].origin, &camera->pos);
		dup_vec(&ray_lst[i].direction, &ray_lst[i - 1].direction);
		add_vec_vec(&ray_lst[i].direction, &screen_vect[0]);
		i++;
	}
}

static void	fill_ray_tab_top(t_ray **ray_tab, t_vector screen_vect[2],
				int number_ray, int number_line)
{
	int	x;
	int	y;

	y = number_line / 2;
	y--;
	while (y >= 0)
	{
		x = 0;
		while (x < number_ray)
		{
			dup_vec(&ray_tab[y][x].direction, &ray_tab[y + 1][x].direction);
			sub_vec_vec(&ray_tab[y][x].direction, &screen_vect[1]);
			dup_vec(&ray_tab[y][x].origin, &ray_tab[y + 1][x].origin);
			x++;
		}
		y--;
	}
}

static void	fill_ray_tab_bot(t_ray **ray_tab, t_vector screen_vect[2],
				int number_ray, int number_line)
{
	int	x;
	int	y;

	y = number_line / 2;
	y++;
	while (y < number_line)
	{
		x = 0;
		while (x < number_ray)
		{
			dup_vec(&ray_tab[y][x].direction, &ray_tab[y - 1][x].direction);
			add_vec_vec(&ray_tab[y][x].direction, &screen_vect[1]);
			dup_vec(&ray_tab[y][x].origin, &ray_tab[y - 1][x].origin);
			x++;
		}
		y++;
	}
}
