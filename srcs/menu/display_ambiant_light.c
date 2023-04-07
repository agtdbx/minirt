/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_ambiant_light.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:35:27 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/07 16:37:30 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
 * Draw and manage the ambiant light into the menu
 */
void	display_ambiant_light(t_all *all, t_light *ambiant_light)
{
	manage_float_range(all, &ambiant_light->brightness, 140, "intensity : ");
	if (manage_color(all, &ambiant_light->color, 180))
	{
		ambiant_light->intensity_r = ambiant_light->color.r / 255.0f;
		ambiant_light->intensity_g = ambiant_light->color.g / 255.0f;
		ambiant_light->intensity_b = ambiant_light->color.b / 255.0f;
	}
	if (all->draw_state != DRAW_TEXT)
		return ;
	my_put_string(all, "AMBIANT LIGHT", WIDTH - 270, 100);
	display_float_range(all, ambiant_light->brightness, 140, "intensity : ");
	display_color(all, &ambiant_light->color, 180);
}
