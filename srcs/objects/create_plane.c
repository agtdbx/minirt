/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:19:02 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/15 11:53:35 by aderouba         ###   ########.fr       */
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
	res.normal_map = NULL;
	return (res);
}

void	delete_plane(t_plane *plane)
{
	if (plane->texture_map)
		mlx_delete_texture(plane->texture_map);
	if (plane->normal_map)
		mlx_delete_texture(plane->normal_map);
}
