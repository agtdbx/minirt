/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:35:27 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/07 16:37:45 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	display_light(t_all *all, t_light *light)
{
	manage_pos(all, &light->pos, 140);
	manage_float_range(all, &light->brightness, 220, "intensity : ");
	if (manage_color(all, &light->color, 260))
	{
		light->intensity_r = light->color.r / 255.0f;
		light->intensity_g = light->color.g / 255.0f;
		light->intensity_b = light->color.b / 255.0f;
	}
	if (all->draw_state != DRAW_TEXT)
		return ;
	my_put_string(all, "LIGHT", WIDTH - 230, 100);
	display_pos(all, &light->pos, 140);
	display_float_range(all, light->brightness, 220, "intensity : ");
	display_color(all, &light->color, 260);
}
