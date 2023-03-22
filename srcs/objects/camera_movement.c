/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:12:15 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/22 13:48:57 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	camera_rotations_arrond_x(t_all *all, const float degrees);
static void	camera_rotations_arrond_y(t_all *all, const float degrees);

void	camera_translations(t_all *all, float delta_time)
{
	const t_vector	go_x = multiply_vect_number(&all->scene.camera.basis[0],
			delta_time * 5.0f);
	const t_vector	go_y = multiply_vect_number(&all->scene.camera.basis[1],
			delta_time * 5.0f);
	const t_vector	go_z = multiply_vect_number(&all->scene.camera.basis[2],
			delta_time * 5.0f);

	if (mlx_is_key_down(all->mlx, MLX_KEY_W))
		all->scene.camera.pos = add_vect_vect(&all->scene.camera.pos, &go_z);
	if (mlx_is_key_down(all->mlx, MLX_KEY_S))
		all->scene.camera.pos = sub_vect_vect(&all->scene.camera.pos, &go_z);
	if (mlx_is_key_down(all->mlx, MLX_KEY_A))
		all->scene.camera.pos = sub_vect_vect(&all->scene.camera.pos, &go_x);
	if (mlx_is_key_down(all->mlx, MLX_KEY_D))
		all->scene.camera.pos = add_vect_vect(&all->scene.camera.pos, &go_x);
	if (mlx_is_key_down(all->mlx, MLX_KEY_SPACE))
		all->scene.camera.pos = sub_vect_vect(&all->scene.camera.pos, &go_y);
	if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT_SHIFT))
		all->scene.camera.pos = add_vect_vect(&all->scene.camera.pos, &go_y);
}

void	camera_rotations(t_all *all, float delta_time)
{
	const float	degrees = delta_time * 15.0f;

	camera_rotations_arrond_x(all, degrees);
	camera_rotations_arrond_y(all, degrees);
}

static void	camera_rotations_arrond_x(t_all *all, const float degrees)
{
	float	len;

	if (mlx_is_key_down(all->mlx, MLX_KEY_UP))
	{
		absolute_rotate(&all->scene.camera.basis[0], degrees, ROTATE_AROUND_X);
		absolute_rotate(&all->scene.camera.basis[1], degrees, ROTATE_AROUND_X);
		absolute_rotate(&all->scene.camera.basis[2], degrees, ROTATE_AROUND_X);
		len = WIDTH / (tan(all->scene.camera.fov * PI_DIV_360) * 2.0f);
		all->scene.camera.orientation = multiply_vect_number(
				&all->scene.camera.basis[2], len);
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_DOWN))
	{
		absolute_rotate(&all->scene.camera.basis[0], -degrees, ROTATE_AROUND_X);
		absolute_rotate(&all->scene.camera.basis[1], -degrees, ROTATE_AROUND_X);
		absolute_rotate(&all->scene.camera.basis[2], -degrees, ROTATE_AROUND_X);
		len = WIDTH / (tan(all->scene.camera.fov * PI_DIV_360) * 2.0f);
		all->scene.camera.orientation = multiply_vect_number(
				&all->scene.camera.basis[2], len);
	}
}

static void	camera_rotations_arrond_y(t_all *all, const float degrees)
{
	float	len;

	if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT))
	{
		absolute_rotate(&all->scene.camera.basis[0], degrees, ROTATE_AROUND_Y);
		absolute_rotate(&all->scene.camera.basis[1], degrees, ROTATE_AROUND_Y);
		absolute_rotate(&all->scene.camera.basis[2], degrees, ROTATE_AROUND_Y);
		len = WIDTH / (tan(all->scene.camera.fov * PI_DIV_360) * 2.0f);
		all->scene.camera.orientation = multiply_vect_number(
				&all->scene.camera.basis[2], len);
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_RIGHT))
	{
		absolute_rotate(&all->scene.camera.basis[0], -degrees, ROTATE_AROUND_Y);
		absolute_rotate(&all->scene.camera.basis[1], -degrees, ROTATE_AROUND_Y);
		absolute_rotate(&all->scene.camera.basis[2], -degrees, ROTATE_AROUND_Y);
		len = WIDTH / (tan(all->scene.camera.fov * PI_DIV_360) * 2.0f);
		all->scene.camera.orientation = multiply_vect_number(
				&all->scene.camera.basis[2], len);
	}
}
