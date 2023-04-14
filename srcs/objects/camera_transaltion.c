/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_transaltion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:15:56 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/14 13:16:35 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	apply_go(t_all *all, t_vector const *go_dir, char operator);
static void	check_input(t_all *all, t_vector const *go_x,
				t_vector const *go_y, t_vector const *go_z);

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
	normalize_vec(&go_z);
	go_y = (t_vector){0.0f, -1.0f, 0.0f};
	multiply_vec_number(&go_x, speed);
	multiply_vec_number(&go_y, speed);
	multiply_vec_number(&go_z, speed);
	check_input(all, &go_x, &go_y, &go_z);
}

static void	check_input(t_all *all, t_vector const *go_x,
			t_vector const *go_y, t_vector const *go_z)
{
	if (mlx_is_key_down(all->mlx, MLX_KEY_W))
		apply_go(all, go_z, '+');
	if (mlx_is_key_down(all->mlx, MLX_KEY_S))
		apply_go(all, go_z, '-');
	if (mlx_is_key_down(all->mlx, MLX_KEY_A))
		apply_go(all, go_x, '-');
	if (mlx_is_key_down(all->mlx, MLX_KEY_D))
		apply_go(all, go_x, '+');
	if (mlx_is_key_down(all->mlx, MLX_KEY_SPACE))
		apply_go(all, go_y, '-');
	if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT_SHIFT))
		apply_go(all, go_y, '+');
}

static void	apply_go(t_all *all, t_vector const *go_dir, char operator)
{
	if (operator == '+')
		add_vec_vec(&all->scene.camera.pos, go_dir);
	else if (operator == '-')
		sub_vec_vec(&all->scene.camera.pos, go_dir);
	all->draw_state = NEED_REDRAW;
}
