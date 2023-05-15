/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_cylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:34:26 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/15 13:21:21 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	manage_intensities(t_all *all, t_cylinder *cylinder);
static void	draw_cylinder_properties(t_all *all, t_cylinder *cylinder);
static void	calculate_ends(t_cylinder *cylinder);

void	display_cylinder(t_all *all, t_cylinder *cylinder)
{
	my_put_string(all, "CYLINDER", WIDTH - 250, 100);
	if (manage_pos(all, &cylinder->origin, 140))
		calculate_ends(cylinder);
	if (manage_dir(all, &cylinder->axis, 220))
	{
		vec3_normalize(&cylinder->axis);
		calculate_ends(cylinder);
	}
	if (manage_float(all, &cylinder->height, 300, "height : "))
		calculate_ends(cylinder);
	if (manage_float(all, &cylinder->radius, 340, "radius : "))
		cylinder->radius2 = cylinder->radius * cylinder->radius;
	manage_color(all, &cylinder->color, 380);
	manage_intensities(all, cylinder);
	if (all->draw_state != DRAW_TEXT)
		return ;
	draw_cylinder_properties(all, cylinder);
}

static void	manage_intensities(t_all *all, t_cylinder *cylinder)
{
	cylinder->shininess_intensity /= 50.0f;
	manage_float_range(all, &cylinder->shininess_intensity, 460,
		"shininess : ");
	cylinder->shininess_intensity *= 50.0f;
	manage_float_range(all, &cylinder->reflexion_intensity, 500,
		"reflexion : ");
	manage_float_range(all, &cylinder->transparency_intensity, 540,
		"transparency : ");
	cylinder->refraction_intensity -= 1.0f;
	cylinder->refraction_intensity *= 20.0f;
	manage_float(all, &cylinder->refraction_intensity, 580,
		"refraction : ");
	cylinder->refraction_intensity /= 20.0f;
	cylinder->refraction_intensity += 1.0f;
}

static void	draw_cylinder_properties(t_all *all, t_cylinder *cylinder)
{
	my_put_string(all, "CYLINDER", WIDTH - 250, 100);
	display_pos(all, &cylinder->origin, 140);
	display_dir(all, &cylinder->axis, 220);
	display_float(all, cylinder->height, 300, "height : ");
	display_float(all, cylinder->radius, 340, "radius : ");
	display_color(all, &cylinder->color, 380);
	display_float_range(all, cylinder->shininess_intensity / 50.0f,
		460, "shininess : ");
	display_float_range(all, cylinder->reflexion_intensity, 500,
		"reflexion : ");
	display_float_range(all, cylinder->transparency_intensity, 540,
		"transparency : ");
	display_float(all, cylinder->refraction_intensity, 580,
		"refraction : ");
}

static void	calculate_ends(t_cylinder *cylinder)
{
	t_vec3		rev_axis;
	float const	half_height = cylinder->height / 2.0f;

	vec3_dup(&rev_axis, &cylinder->axis);
	vec3_multiply_number(&rev_axis, -1.0f);
	vec3_dup(&cylinder->bot_origin, &cylinder->origin);
	cylinder->bot_origin.x += rev_axis.x * half_height;
	cylinder->bot_origin.y += rev_axis.y * half_height;
	cylinder->bot_origin.z += rev_axis.z * half_height;
	vec3_dup(&cylinder->top_origin, &cylinder->origin);
	cylinder->top_origin.x += cylinder->axis.x * half_height;
	cylinder->top_origin.y += cylinder->axis.y * half_height;
	cylinder->top_origin.z += cylinder->axis.z * half_height;
	cylinder->bot = create_plane(cylinder->bot_origin, rev_axis,
			cylinder->color);
	cylinder->bot.mapping_type = cylinder->mapping_type;
	cylinder->top = create_plane(cylinder->top_origin, cylinder->axis,
			cylinder->color);
	cylinder->top.mapping_type = cylinder->mapping_type;
}
