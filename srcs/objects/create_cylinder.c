/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:29:55 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/16 14:56:56 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	init_ends(t_cylinder *cylinder);
static void	init_intensities(t_cylinder *cylinder);

t_cylinder	create_cylinder(t_vec3 origin, t_vec3 axis, float size[2],
				t_color color)
{
	t_cylinder	res;

	res.radius = size[0] / 2.0f;
	res.radius2 = res.radius * res.radius;
	res.height = size[1];
	res.color = color;
	res.id = -1;
	res.mapping_type = MAP_COLOR;
	res.texture_map = NULL;
	// res.texture_map = mlx_load_png("img/gravel_texture.png");
	// res.texture_map = mlx_load_png("img/test.png");
	res.normal_map = NULL;
	// res.normal_map = mlx_load_png("img/gravel_normal.png");
	vec3_dup(&res.origin, &origin);
	vec3_dup(&res.axis, &axis);
	init_ends(&res);
	init_intensities(&res);
	return (res);
}

static void	init_ends(t_cylinder *cylinder)
{
	t_vec3		rev_axis;

	vec3_dup(&rev_axis, &cylinder->axis);
	vec3_multiply_number(&rev_axis, -1.0f);
	vec3_dup(&cylinder->bot_origin, &cylinder->origin);
	cylinder->bot_origin.x += rev_axis.x * (cylinder->height / 2.0f);
	cylinder->bot_origin.y += rev_axis.y * (cylinder->height / 2.0f);
	cylinder->bot_origin.z += rev_axis.z * (cylinder->height / 2.0f);
	cylinder->bot = create_plane_for_cylinder(cylinder->bot_origin, rev_axis, cylinder);
	vec3_dup(&cylinder->top_origin, &cylinder->origin);
	cylinder->top_origin.x += cylinder->axis.x * (cylinder->height / 2.0f);
	cylinder->top_origin.y += cylinder->axis.y * (cylinder->height / 2.0f);
	cylinder->top_origin.z += cylinder->axis.z * (cylinder->height / 2.0f);
	cylinder->top = create_plane_for_cylinder(cylinder->top_origin, cylinder->axis, cylinder);
}

static void	init_intensities(t_cylinder *cylinder)
{
	cylinder->shininess_intensity = 10.0f;
	cylinder->reflexion_intensity = 0.0f;
	cylinder->transparency_intensity = 0.0f;
	cylinder->refraction_intensity = 1.0f;
}

void	delete_cylinder(t_cylinder *cylinder)
{
	if (cylinder->texture_map)
		mlx_delete_texture(cylinder->texture_map);
	if (cylinder->normal_map)
		mlx_delete_texture(cylinder->normal_map);
}
