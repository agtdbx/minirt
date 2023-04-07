/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_cylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:34:26 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/07 16:37:35 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	calculate_ends(t_cylinder *cylinder);

void	display_cylinder(t_all *all, t_cylinder *cylinder)
{
	my_put_string(all, "CYLINDER", WIDTH - 250, 100);
	if (manage_pos(all, &cylinder->origin, 140))
		calculate_ends(cylinder);
	if (manage_dir(all, &cylinder->axis, 220))
	{
		normalize_vec(&cylinder->axis);
		calculate_ends(cylinder);
	}
	if (manage_float(all, &cylinder->height, 300, "height : "))
		calculate_ends(cylinder);
	if (manage_float(all, &cylinder->radius, 340, "radius : "))
		cylinder->radius2 = cylinder->radius * cylinder->radius;
	manage_color(all, &cylinder->color, 380);
	manage_float_range(all, &cylinder->reflexion_intensity, 460,
		"reflexion : ");
	if (all->draw_state != DRAW_TEXT)
		return ;
	my_put_string(all, "CYLINDER", WIDTH - 250, 100);
	display_pos(all, &cylinder->origin, 140);
	display_dir(all, &cylinder->axis, 220);
	display_float(all, cylinder->height, 300, "height : ");
	display_float(all, cylinder->radius, 340, "radius : ");
	display_color(all, &cylinder->color, 380);
	display_float_range(all, cylinder->reflexion_intensity, 460,
		"reflexion : ");
}

static void	calculate_ends(t_cylinder *cylinder)
{
	t_vector	rev_axis;
	float const	half_height = cylinder->height / 2.0f;

	dup_vec(&rev_axis, &cylinder->axis);
	multiply_vec_number(&rev_axis, -1.0f);
	dup_vec(&cylinder->bot_origin, &cylinder->origin);
	cylinder->bot_origin.x += rev_axis.x * half_height;
	cylinder->bot_origin.y += rev_axis.y * half_height;
	cylinder->bot_origin.z += rev_axis.z * half_height;
	dup_vec(&cylinder->top_origin, &cylinder->origin);
	cylinder->top_origin.x += cylinder->axis.x * half_height;
	cylinder->top_origin.y += cylinder->axis.y * half_height;
	cylinder->top_origin.z += cylinder->axis.z * half_height;
	cylinder->bot = create_plane(cylinder->bot_origin, rev_axis,
			cylinder->color);
	cylinder->top = create_plane(cylinder->top_origin, cylinder->axis,
			cylinder->color);
}