/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:41:13 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/17 16:14:38 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static bool	direct_set_ppr(t_all *all);

void	ppr_gestion(t_all *all, float delta_time)
{
	static float	time_ignore_input = 0.0f;

	if (time_ignore_input > 0.0f)
	{
		time_ignore_input -= delta_time;
		if (time_ignore_input < 0.0f)
			time_ignore_input = 0.0f;
	}
	if (direct_set_ppr(all))
		return ;
	if (mlx_is_key_down(all->mlx, MLX_KEY_EQUAL) && all->scene.ppr < 9
		&& time_ignore_input == 0.0f)
	{
		all->scene.ppr++;
		time_ignore_input = 1.0f;
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_MINUS) && all->scene.ppr > 1
		&& time_ignore_input == 0.0f)
	{
		all->scene.ppr--;
		time_ignore_input = 1.0f;
	}
}

static bool	direct_set_ppr(t_all *all)
{
	int	key_check;

	key_check = MLX_KEY_1;
	while (key_check <= MLX_KEY_9)
	{
		if (mlx_is_key_down(all->mlx, key_check))
		{
			all->scene.ppr = key_check - MLX_KEY_0;
			return (true);
		}
		key_check++;
	}
	return (false);
}
