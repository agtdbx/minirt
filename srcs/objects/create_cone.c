/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:01:53 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/22 11:53:25 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_cone	create_cone(t_vec3 origin, t_vec3 axis, float size[2],
			t_color color)
{
	t_cone	res;
	t_vec3	tmp;

	res.radius = size[0] / 2.0f;
	res.radius2 = res.radius * res.radius;
	res.height = size[1];
	res.color = color;
	res.id = -1;
	res.mapping_type = MAP_COLOR;
	res.texture_map = NULL;
	// res.texture_map = mlx_load_png("img/Bark_texture.png");
	// res.texture_map = mlx_load_png("img/gravel_texture.png");
	// res.texture_map = mlx_load_png("img/test.png");
	res.normal_map = NULL;
	// res.normal_map = mlx_load_png("img/gravel_normal.png");
	// res.normal_map = mlx_load_png("img/Bark_normal.png");
	vec3_dup(&res.origin, &origin);
	vec3_dup(&res.axis, &axis);
	vec3_normalize(&res.axis);
	vec3_dup(&tmp, &res.axis);
	vec3_multiply_number(&tmp, res.height);
	vec3_dup(&res.end_pos, &origin);
	vec3_add_vec3(&res.end_pos, &tmp);
	res.end = create_plane_for_cone(res.end_pos, res.axis, &res);
	res.shininess_intensity = 10.0f;
	res.reflexion_intensity = 0.0f;
	res.transparency_intensity = 0.0f;
	res.refraction_intensity = 1.0f;
	return (res);
}
