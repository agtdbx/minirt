/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:41:56 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/15 17:49:33 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_sphere	create_sphere(t_vec3 origin, float diameter, t_color color)
{
	t_sphere	res;

	vec3_dup(&res.origin, &origin);
	res.radius = diameter / 2.0f;
	res.radius2 = res.radius * res.radius;
	res.color = color;
	res.id = -1;
	res.shininess_intensity = 10.0f;
	res.reflexion_intensity = 0.0f;
	res.transparency_intensity = 0.0f;
	res.refraction_intensity = 1.0f;
	res.mapping_type = MAP_CHECKERBOARD;
	res.texture_map = NULL;
	// res.texture_map = mlx_load_png("img/gravel_texture.png");
	// res.texture_map = mlx_load_png("img/test.png");
	res.normal_map = NULL;
	res.normal_map = mlx_load_png("img/gravel_normal.png");
	return (res);
}

t_sphere	create_sphere_from_light(t_light *light)
{
	t_sphere	res;

	vec3_dup(&res.origin, &light->pos);
	res.radius = 0.25f;
	res.radius2 = res.radius * res.radius;
	res.color = light->color;
	res.id = SELECT_LIGHT;
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
