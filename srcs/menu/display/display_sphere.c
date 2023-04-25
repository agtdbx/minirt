/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:34:26 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/25 13:49:05 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	display_properties(t_all *all, t_sphere *sphere);

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
	manage_float_range(all, &sphere->transparency_intensity, 420,
		"transparency : ");
	sphere->refraction_intensity -= 1.0f;
	manage_float_range(all, &sphere->refraction_intensity, 460,
		"refraction : ");
	sphere->refraction_intensity += 1.0f;
	if (all->draw_state != DRAW_TEXT)
		return ;
	display_properties(all, sphere);
}

static void	display_properties(t_all *all, t_sphere *sphere)
{
	my_put_string(all, "SPHERE", WIDTH - 240, 100);
	display_pos(all, &sphere->origin, 140);
	display_float(all, sphere->radius, 220, "radius : ");
	display_color(all, &sphere->color, 260);
	display_float_range(all, sphere->shininess_intensity / 50.0f, 340,
		"shininess : ");
	display_float_range(all, sphere->reflexion_intensity, 380, "reflexion : ");
	display_float_range(all, sphere->transparency_intensity, 420,
		"transparency : ");
	display_float_range(all, sphere->refraction_intensity, 460,
		"refraction : ");
}
