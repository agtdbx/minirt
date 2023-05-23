/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:19:02 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/23 18:16:31 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_plane	create_plane(t_vec3 origin, t_vec3 normal, t_color color)
{
	t_plane	res;

	res.origin = origin;
	res.normal = normal;
	vec3_dup(&res.rev_normal, &res.normal);
	vec3_multiply_number(&res.rev_normal, -1.0f);
	res.color = color;
	res.id = -1;
	res.shininess_intensity = 10.0f;
	res.reflexion_intensity = 0.0f;
	res.transparency_intensity = 0.0f;
	res.refraction_intensity = 1.0f;
	res.mapping_type = MAP_COLOR;
	res.texture_map = NULL;
	// res.texture_map = mlx_load_png("img/Stylized_Stone_texture.png");
	// res.texture_map = mlx_load_png("img/gravel_texture.png");
	// res.texture_map = mlx_load_png("img/test.png");
	res.normal_map = NULL;
	// res.normal_map = mlx_load_png("img/Stylized_Stone_normal.png");
	// res.normal_map = mlx_load_png("img/gravel_normal.png");
	// res.normal_map = mlx_load_png("img/test.png");
	return (res);
}

t_plane	create_plane_for_cylinder(t_vec3 origin, t_vec3 normal,
			t_cylinder *cylinder)
{
	t_plane	res;

	res.origin = origin;
	res.normal = normal;
	vec3_dup(&res.rev_normal, &res.normal);
	vec3_multiply_number(&res.rev_normal, -1.0f);
	res.color = cylinder->color;
	res.id = cylinder->id;
	res.shininess_intensity = cylinder->shininess_intensity;
	res.reflexion_intensity = cylinder->reflexion_intensity;
	res.transparency_intensity = cylinder->transparency_intensity;
	res.refraction_intensity = cylinder->refraction_intensity;
	res.mapping_type = cylinder->mapping_type;
	res.texture_map = cylinder->texture_map;
	res.normal_map = cylinder->normal_map;
	return (res);
}

t_plane	create_plane_for_cone(t_vec3 origin, t_vec3 normal,
			t_cone *cone)
{
	t_plane	res;

	res.origin = origin;
	res.normal = normal;
	vec3_dup(&res.rev_normal, &res.normal);
	vec3_multiply_number(&res.rev_normal, -1.0f);
	res.color = cone->color;
	res.id = cone->id;
	res.shininess_intensity = cone->shininess_intensity;
	res.reflexion_intensity = cone->reflexion_intensity;
	res.transparency_intensity = cone->transparency_intensity;
	res.refraction_intensity = cone->refraction_intensity;
	res.mapping_type = cone->mapping_type;
	res.texture_map = cone->texture_map;
	res.normal_map = cone->normal_map;
	return (res);
}

void	delete_plane(t_plane *plane)
{
	if (plane->texture_map)
		mlx_delete_texture(plane->texture_map);
	if (plane->normal_map)
		mlx_delete_texture(plane->normal_map);
}
