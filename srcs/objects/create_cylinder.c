/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:29:55 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/25 13:22:56 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	init_intensities(t_cylinder *cylinder);

t_cylinder	create_cylinder(t_vec3 origin, t_vec3 axis, float size[2],
				t_color color)
{
	t_cylinder	res;
	t_vec3		rev_axis;

	vec3_dup(&rev_axis, &axis);
	vec3_multiply_number(&rev_axis, -1.0f);
	res.radius = size[0] / 2.0f;
	res.radius2 = res.radius * res.radius;
	res.height = size[1];
	vec3_dup(&res.origin, &origin);
	vec3_dup(&res.bot_origin, &origin);
	res.bot_origin.x += rev_axis.x * (res.height / 2.0f);
	res.bot_origin.y += rev_axis.y * (res.height / 2.0f);
	res.bot_origin.z += rev_axis.z * (res.height / 2.0f);
	vec3_dup(&res.top_origin, &origin);
	res.top_origin.x += axis.x * (res.height / 2.0f);
	res.top_origin.y += axis.y * (res.height / 2.0f);
	res.top_origin.z += axis.z * (res.height / 2.0f);
	res.bot = create_plane(res.bot_origin, rev_axis, color);
	res.top = create_plane(res.top_origin, axis, color);
	vec3_dup(&res.axis, &axis);
	res.color = color;
	res.id = -1;
	init_intensities(&res);
	return (res);
}

static void	init_intensities(t_cylinder *cylinder)
{
	cylinder->shininess_intensity = 10.0f;
	cylinder->reflexion_intensity = 0.0f;
	cylinder->transparency_intensity = 0.0f;
	cylinder->refraction_intensity = 1.3f;
}
