/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:34:26 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/26 09:58:02 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	display_properties(t_all *all, t_plane *plane);

void	display_plane(t_all *all, t_plane *plane)
{
	manage_pos(all, &plane->origin, 140);
	if (manage_dir(all, &plane->normal, 220))
	{
		vec3_normalize(&plane->normal);
		vec3_dup(&plane->rev_normal, &plane->normal);
		vec3_multiply_number(&plane->rev_normal, -1.0f);
	}
	manage_color(all, &plane->color, 300);
	plane->shininess_intensity /= 50.0f;
	manage_float_range(all, &plane->shininess_intensity, 380, "shininess : ");
	plane->shininess_intensity *= 50.0f;
	manage_float_range(all, &plane->reflexion_intensity, 420, "reflexion : ");
	manage_float_range(all, &plane->transparency_intensity, 460,
		"transparency : ");
	if (all->draw_state != DRAW_TEXT)
		return ;
	display_properties(all, plane);
}

static void	display_properties(t_all *all, t_plane *plane)
{
	my_put_string(all, "PLANE", WIDTH - 230, 100);
	display_pos(all, &plane->origin, 140);
	display_dir(all, &plane->normal, 220);
	display_color(all, &plane->color, 300);
	display_float_range(all, plane->shininess_intensity / 50.0f, 380,
		"shininess : ");
	display_float_range(all, plane->reflexion_intensity, 420, "reflexion : ");
	display_float_range(all, plane->transparency_intensity, 460,
		"transparency : ");
}
