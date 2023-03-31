/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:12:15 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/31 15:35:47 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	camera_rotations_arrond_x(t_all *all, const float degrees);
static void	camera_rotations_arrond_y(t_all *all, const float degrees);

void	camera_translations(t_all *all, float delta_time)
{
	t_vector	go_x;
	t_vector	go_y;
	t_vector	go_z;
	const float	speed = delta_time * 5.0f;

	dup_vec(&go_x, &all->scene.camera.basis[0]);
	dup_vec(&go_z, &all->scene.camera.basis[2]);
	go_x.y = 0.0f;
	go_z.y = 0.0f;
	go_y = (t_vector){0.0f, -1.0f, 0.0f};
	multiply_vec_number(&go_x, speed);
	multiply_vec_number(&go_y, speed);
	multiply_vec_number(&go_z, speed);
	if (mlx_is_key_down(all->mlx, MLX_KEY_W))
		add_vec_vec(&all->scene.camera.pos, &go_z);
	if (mlx_is_key_down(all->mlx, MLX_KEY_S))
		sub_vec_vec(&all->scene.camera.pos, &go_z);
	if (mlx_is_key_down(all->mlx, MLX_KEY_A))
		sub_vec_vec(&all->scene.camera.pos, &go_x);
	if (mlx_is_key_down(all->mlx, MLX_KEY_D))
		add_vec_vec(&all->scene.camera.pos, &go_x);
	if (mlx_is_key_down(all->mlx, MLX_KEY_SPACE))
		sub_vec_vec(&all->scene.camera.pos, &go_y);
	if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT_SHIFT))
		add_vec_vec(&all->scene.camera.pos, &go_y);
}

void	camera_rotations(t_all *all, float delta_time)
{
	const float	degrees = delta_time * 20.0f;

	camera_rotations_arrond_x(all, degrees);
	camera_rotations_arrond_y(all, degrees);
}

static void	camera_rotations_arrond_x(t_all *all, const float degrees)
{
	float		len;	
	const float	rad = degrees * PI_DIV_180;

	if (mlx_is_key_down(all->mlx, MLX_KEY_UP))
	{
		my_rot_around(
			&all->scene.camera.basis[1], &all->scene.camera.basis[0], rad);
		my_rot_around(
			&all->scene.camera.basis[2], &all->scene.camera.basis[0], rad);
		len = WIDTH / (tan(all->scene.camera.fov * PI_DIV_360) * 2.0f);
		dup_vec(&all->scene.camera.orientation, &all->scene.camera.basis[2]);
		multiply_vec_number(&all->scene.camera.orientation, len);
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_DOWN))
	{
		my_rot_around(
			&all->scene.camera.basis[1], &all->scene.camera.basis[0], -rad);
		my_rot_around(
			&all->scene.camera.basis[2], &all->scene.camera.basis[0], -rad);
		len = WIDTH / (tan(all->scene.camera.fov * PI_DIV_360) * 2.0f);
		dup_vec(&all->scene.camera.orientation, &all->scene.camera.basis[2]);
		multiply_vec_number(&all->scene.camera.orientation, len);
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
		dup_vec(&all->scene.camera.orientation, &all->scene.camera.basis[2]);
		multiply_vec_number(&all->scene.camera.orientation, len);
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_RIGHT))
	{
		absolute_rotate(&all->scene.camera.basis[0], -degrees, ROTATE_AROUND_Y);
		absolute_rotate(&all->scene.camera.basis[1], -degrees, ROTATE_AROUND_Y);
		absolute_rotate(&all->scene.camera.basis[2], -degrees, ROTATE_AROUND_Y);
		len = WIDTH / (tan(all->scene.camera.fov * PI_DIV_360) * 2.0f);
		dup_vec(&all->scene.camera.orientation, &all->scene.camera.basis[2]);
		multiply_vec_number(&all->scene.camera.orientation, len);
	}
}
