/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:15:56 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/14 13:24:29 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	camera_rotations_arrond_x(t_all *all, const float degrees,
				t_vector basis[3]);
static void	camera_rotations_arrond_y(t_all *all, const float degrees);

void	camera_rotations(t_all *all, float delta_time)
{
	const float	degrees = delta_time * 20.0f;

	camera_rotations_arrond_x(all, degrees, all->scene.camera.basis);
	camera_rotations_arrond_y(all, degrees);
}

static void	camera_rotations_arrond_x(t_all *all, const float degrees,
			t_vector basis[3])
{
	const float	rad = degrees * PI_DIV_180;

	if (mlx_is_key_down(all->mlx, MLX_KEY_UP))
	{
		relative_rotate(&basis[1], &basis[0], rad);
		relative_rotate(&basis[2], &basis[0], rad);
		dup_vec(&all->scene.camera.orientation, &basis[2]);
		multiply_vec_number(&all->scene.camera.orientation,
			all->scene.camera.len);
		all->draw_state = NEED_REDRAW;
	}
	if (all->scene.camera.basis[2].z > 0.1f
		&& mlx_is_key_down(all->mlx, MLX_KEY_DOWN))
	{
		relative_rotate(&basis[1], &basis[0], -rad);
		relative_rotate(&basis[2], &basis[0], -rad);
		dup_vec(&all->scene.camera.orientation, &basis[2]);
		multiply_vec_number(&all->scene.camera.orientation,
			all->scene.camera.len);
		all->draw_state = NEED_REDRAW;
	}
}

static void	camera_rotations_arrond_y(t_all *all, const float degrees)
{
	if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT))
	{
		absolute_rotate(&all->scene.camera.basis[0], degrees, ROTATE_AROUND_Y);
		absolute_rotate(&all->scene.camera.basis[1], degrees, ROTATE_AROUND_Y);
		absolute_rotate(&all->scene.camera.basis[2], degrees, ROTATE_AROUND_Y);
		dup_vec(&all->scene.camera.orientation, &all->scene.camera.basis[2]);
		multiply_vec_number(&all->scene.camera.orientation,
			all->scene.camera.len);
		all->draw_state = NEED_REDRAW;
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_RIGHT))
	{
		absolute_rotate(&all->scene.camera.basis[0], -degrees, ROTATE_AROUND_Y);
		absolute_rotate(&all->scene.camera.basis[1], -degrees, ROTATE_AROUND_Y);
		absolute_rotate(&all->scene.camera.basis[2], -degrees, ROTATE_AROUND_Y);
		dup_vec(&all->scene.camera.orientation, &all->scene.camera.basis[2]);
		multiply_vec_number(&all->scene.camera.orientation,
			all->scene.camera.len);
		all->draw_state = NEED_REDRAW;
	}
}
