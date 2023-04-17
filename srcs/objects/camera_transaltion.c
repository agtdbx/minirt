/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_transaltion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:15:56 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/17 16:21:39 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	apply_go(t_all *all, t_vec3 const *go_dir, char operator);
static void	check_input(t_all *all, t_vec3 const *go_x,
				t_vec3 const *go_y, t_vec3 const *go_z);

void	camera_translations(t_all *all, float delta_time)
{
	t_vec3		go_x;
	t_vec3		go_y;
	t_vec3		go_z;
	const float	speed = delta_time * 5.0f;

	vec3_dup(&go_x, &all->scene.camera.basis[0]);
	vec3_dup(&go_z, &all->scene.camera.basis[2]);
	go_x.y = 0.0f;
	go_z.y = 0.0f;
	vec3_normalize(&go_z);
	go_y = (t_vec3){0.0f, -1.0f, 0.0f};
	vec3_multiply_number(&go_x, speed);
	vec3_multiply_number(&go_y, speed);
	vec3_multiply_number(&go_z, speed);
	check_input(all, &go_x, &go_y, &go_z);
}

static void	check_input(t_all *all, t_vec3 const *go_x,
			t_vec3 const *go_y, t_vec3 const *go_z)
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

static void	apply_go(t_all *all, t_vec3 const *go_dir, char operator)
{
	if (operator == '+')
		vec3_add_vec3(&all->scene.camera.pos, go_dir);
	else if (operator == '-')
		vec3_sub_vec3(&all->scene.camera.pos, go_dir);
	all->draw_state = NEED_REDRAW;
}
