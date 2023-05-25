/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_cone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:34:26 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/24 12:00:44 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	manage_intensities(t_all *all, t_cone *cone);
static void	draw_cone_properties(t_all *all, t_cone *cone);
static void	calculate_end(t_cone *cone);

void	display_cone(t_all *all, t_cone *cone)
{
	my_put_string(all, "cone", WIDTH - 250, 100);
	manage_pos(all, &cone->origin, 140);
	if (manage_dir(all, &cone->axis, 220))
		vec3_normalize(&cone->axis);
	manage_float(all, &cone->height, 300, "height : ");
	if (manage_float(all, &cone->radius, 340, "radius : "))
		cone->radius2 = cone->radius * cone->radius;
	if (manage_color(all, &cone->color, 380))
		cone->end.color = cone->color;
	manage_intensities(all, cone);
	if (all->draw_state != DRAW_TEXT)
		return ;
	draw_cone_properties(all, cone);
}

static void	manage_intensities(t_all *all, t_cone *cone)
{
	cone->shininess_intensity /= 50.0f;
	manage_float_range(all, &cone->shininess_intensity, 460,
		"shininess : ");
	cone->shininess_intensity *= 50.0f;
	manage_float_range(all, &cone->reflexion_intensity, 500,
		"reflexion : ");
	manage_float_range(all, &cone->transparency_intensity, 540,
		"transparency : ");
	cone->refraction_intensity -= 1.0f;
	cone->refraction_intensity *= 20.0f;
	manage_float(all, &cone->refraction_intensity, 580,
		"refraction : ");
	cone->refraction_intensity /= 20.0f;
	cone->refraction_intensity += 1.0f;
	calculate_end(cone);
}

static void	draw_cone_properties(t_all *all, t_cone *cone)
{
	my_put_string(all, "cone", WIDTH - 250, 100);
	display_pos(all, &cone->origin, 140);
	display_dir(all, &cone->axis, 220);
	display_float(all, cone->height, 300, "height : ");
	display_float(all, cone->radius, 340, "radius : ");
	display_color(all, &cone->color, 380);
	display_float_range(all, cone->shininess_intensity / 50.0f,
		460, "shininess : ");
	display_float_range(all, cone->reflexion_intensity, 500,
		"reflexion : ");
	display_float_range(all, cone->transparency_intensity, 540,
		"transparency : ");
	display_float(all, cone->refraction_intensity, 580,
		"refraction : ");
}

static void	calculate_end(t_cone *cone)
{
	vec3_dup(&cone->end_pos, &cone->origin);
	cone->end_pos.x += cone->axis.x * cone->height;
	cone->end_pos.y += cone->axis.y * cone->height;
	cone->end_pos.z += cone->axis.z * cone->height;

	cone->end = create_plane_for_cone(cone->end_pos, cone->axis, cone);
}
