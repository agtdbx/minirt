/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:29:55 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/17 15:09:00 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_cylinder	create_cylinder(t_vector origin, t_vector axis, float size[2],
				t_color color)
{
	t_cylinder	res;
	t_vector	rev_axis;

	dup_vec(&rev_axis, &axis);
	multiply_vec_number(&rev_axis, -1.0f);
	res.radius = size[0] / 2.0f;
	res.radius2 = res.radius * res.radius;
	res.height = size[1];
	dup_vec(&res.origin, &origin);
	dup_vec(&res.bot_origin, &origin);
	res.bot_origin.x += rev_axis.x * (res.height / 2.0f);
	res.bot_origin.y += rev_axis.y * (res.height / 2.0f);
	res.bot_origin.z += rev_axis.z * (res.height / 2.0f);
	dup_vec(&res.top_origin, &origin);
	res.top_origin.x += axis.x * (res.height / 2.0f);
	res.top_origin.y += axis.y * (res.height / 2.0f);
	res.top_origin.z += axis.z * (res.height / 2.0f);
	res.bot = create_plane(res.bot_origin, rev_axis, color);
	res.top = create_plane(res.top_origin, axis, color);
	dup_vec(&res.axis, &axis);
	res.color = color;
	res.id = -1;
	res.shininess_intensity = 10.0f;
	res.reflexion_intensity = 0.0f;
	return (res);
}
