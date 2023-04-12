/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:34:26 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/12 14:38:19 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	display_sphere(t_all *all, t_sphere *sphere)
{
	manage_pos(all, &sphere->origin, 140);
	if (manage_float(all, &sphere->radius, 220, "radius : "))
		sphere->radius2 = sphere->radius * sphere->radius;
	manage_color(all, &sphere->color, 260);
	sphere->shininess_intensity /= 50.0f;
	manage_float_range(all, &sphere->shininess_intensity, 340, "shininess : ");
	sphere->shininess_intensity *= 50.0f;
	manage_float_range(all, &sphere->reflexion_intensity, 380, "reflexion : ");
	if (all->draw_state != DRAW_TEXT)
		return ;
	my_put_string(all, "SPHERE", WIDTH - 240, 100);
	display_pos(all, &sphere->origin, 140);
	display_float(all, sphere->radius, 220, "radius : ");
	display_color(all, &sphere->color, 260);
	display_float_range(all, sphere->shininess_intensity / 50.0f, 340, "shininess : ");
	display_float_range(all, sphere->reflexion_intensity, 380, "reflexion : ");
}
