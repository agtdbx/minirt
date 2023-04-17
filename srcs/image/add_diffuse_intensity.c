/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_diffuse_intensity.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:19:24 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/17 16:17:44 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static bool	is_in_shadow(t_all *all, t_ray *ray, float distance, int id_ignore);

bool	add_diffuse_intensity(t_all *all, t_intersect_ret *res,
			t_light const *light, t_vec3 const *pixel_pos)
{
	float	intensity;
	float	distance;
	float	distance_intensity;
	float	angle_ratio;
	t_ray	ray_from_light;

	if (light->brightness == 0.0f)
		return (false);
	vec3_dup(&ray_from_light.origin, &light->pos);
	vec3_dup(&ray_from_light.direction, pixel_pos);
	vec3_sub_vec3(&ray_from_light.direction, &light->pos);
	distance = vec3_get_length(&ray_from_light.direction);
	if (distance >= LIGHT_DIFFUSE_RADIUS)
		return (false);
	vec3_normalize(&ray_from_light.direction);
	angle_ratio = -vec3_dot_product(&res->nrm, &ray_from_light.direction);
	if (angle_ratio < 0.0f)
		return (false);
	if (is_in_shadow(all, &ray_from_light, distance, res->id))
		return (false);
	distance_intensity = 1.0f - (distance / LIGHT_DIFFUSE_RADIUS);
	intensity = angle_ratio * distance_intensity
		* REFLECTION_DIFFUSE_RATIO;
	incremente_intensity(res, light, intensity);
	return (true);
}

static bool	is_in_shadow(t_all *all, t_ray *ray, float distance, int id_ignore)
{
	t_intersect_ret	res;
	t_rtlst			*obj;

	init_intersect_ret(&res);
	obj = all->scene.objects;
	while (obj)
	{
		if (obj->id != id_ignore)
		{
			if (obj->type == SPHERE)
				intersect_sphere(&obj->value.as_sphere, ray, &res);
			else if (obj->type == PLANE)
				intersect_plane(&obj->value.as_plane, ray, &res);
			else if (obj->type == CYLINDER)
				intersect_cylinder(&obj->value.as_cylinder, ray, &res);
			if (res.dst != -1.0f && res.dst < distance)
				return (true);
		}
		obj = obj->next;
	}
	return (res.dst != -1.0f && res.dst < distance);
}
