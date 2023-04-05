/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:35:27 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/05 16:58:07 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	display_light(t_all *all, t_light *light)
{
	manage_pos(all, &light->pos, 140);
	manage_intensity(all, &light->brightness, 220);
	if (manage_color(all, &light->color, 260))
	{
		light->intensity_r = light->color.r / 255.0f;
		light->intensity_g = light->color.g / 255.0f;
		light->intensity_b = light->color.b / 255.0f;
	}
	if (all->draw_state != DRAW_TEXT)
		return ;
	mlx_put_string(all->mlx, "LIGHT", WIDTH - 230, 100);
	display_pos(all, &light->pos, 140);
	display_intensity(all, light->brightness, 220);
	display_color(all, &light->color, 260);
}
