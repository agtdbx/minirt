/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:34:26 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/12 12:19:12 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	display_plane(t_all *all, t_plane *plane)
{
	manage_pos(all, &plane->origin, 140);
	if (manage_dir(all, &plane->normal, 220))
	{
		normalize_vec(&plane->normal);
		dup_vec(&plane->rev_normal, &plane->normal);
		multiply_vec_number(&plane->rev_normal, -1.0f);
	}
	manage_color(all, &plane->color, 300);
	plane->shininess_intensity -= 1.0f;
	manage_float(all, &plane->shininess_intensity, 380, "shininess : ");
	plane->shininess_intensity += 1.0f;
	manage_float_range(all, &plane->reflexion_intensity, 420, "reflexion : ");
	if (all->draw_state != DRAW_TEXT)
		return ;
	my_put_string(all, "PLANE", WIDTH - 230, 100);
	display_pos(all, &plane->origin, 140);
	display_dir(all, &plane->normal, 220);
	display_color(all, &plane->color, 300);
	display_float(all, plane->shininess_intensity, 380, "shininess : ");
	display_float_range(all, plane->reflexion_intensity, 420, "reflexion : ");
}
