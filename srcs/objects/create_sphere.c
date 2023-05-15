/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:41:56 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/15 11:44:40 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_sphere	create_sphere(t_vec3 origin, float diameter, t_color color)
{
	t_sphere	res;

	res.origin = origin;
	res.radius = diameter / 2.0f;
	res.radius2 = res.radius * res.radius;
	res.color = color;
	res.id = -1;
	res.shininess_intensity = 10.0f;
	res.reflexion_intensity = 0.0f;
	res.transparency_intensity = 0.0f;
	res.refraction_intensity = 1.0f;
	res.mapping_type = MAP_COLOR;
	res.texture_map = NULL;
	res.normal_map = NULL;
	return (res);
}

void	delete_sphere(t_sphere *sphere)
{
	if (sphere->texture_map)
		mlx_delete_texture(sphere->texture_map);
	if (sphere->normal_map)
		mlx_delete_texture(sphere->normal_map);
}
