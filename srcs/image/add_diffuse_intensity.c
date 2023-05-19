/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_diffuse_intensity.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:19:24 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/19 13:13:33 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static bool		is_intersect_light(t_intersect_ret *res,
					t_light const *light);
static float	shadow_intersect(t_all *all, t_ray *ray, float distance,
					int id_ignore);
static void		manage_intersect(t_rtlst *obj, t_intersect_ret *res,
					t_ray *ray);

bool	add_diffuse_intensity(t_all *all, t_intersect_ret *res,
			t_light const *light, t_vec3 const *pixel_pos)
{
	float	intensity;
	float	distance;
	float	distance_intensity;
	float	angle_ratio;
	t_ray	ray_from_light;

	if (light->brightness == 0.0f || is_intersect_light(res, light))
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
	intensity = shadow_intersect(all, &ray_from_light, distance, res->id);
	if (intensity <= 0.0f)
		return (false);
	distance_intensity = 1.0f - (distance / LIGHT_DIFFUSE_RADIUS);
	intensity *= angle_ratio * distance_intensity * REFLECTION_DIFFUSE_RATIO;
	incremente_intensity(res, light, intensity);
	return (true);
}

static bool	is_intersect_light(t_intersect_ret *res,
				t_light const *light)
{
	if (res->id <= -4)
	{
		res->intensity_r += light->brightness;
		res->intensity_g += light->brightness;
		res->intensity_b += light->brightness;
		if (res->intensity_r > 1.0f)
			res->intensity_r = 1.0f;
		if (res->intensity_g > 1.0f)
			res->intensity_g = 1.0f;
		if (res->intensity_b > 1.0f)
			res->intensity_b = 1.0f;
		return (true);
	}
	return (false);
}

static float	shadow_intersect(t_all *all, t_ray *ray, float distance,
					int id_ignore)
{
	t_intersect_ret	res;
	t_rtlst			*obj;
	float			transparency;
	int				nb_intersect;

	init_intersect_ret(&res, 0);
	obj = all->scene.objects;
	transparency = 1.0f;
	nb_intersect = 0;
	while (obj && transparency > 0.0f)
	{
		if (obj->id != id_ignore)
		{
			manage_intersect(obj, &res, ray);
			if (res.dst != -1.0f && res.dst < distance)
			{
				transparency -= (1.0f - res.transparency_intensity);
				nb_intersect++;
			}
		}
		obj = obj->next;
	}
	if (nb_intersect == 0)
		return (1.0f);
	return (transparency);
}

static void	manage_intersect(t_rtlst *obj, t_intersect_ret *res, t_ray *ray)
{
	res->dst = -1.0f;
	if (obj->type == SPHERE)
		intersect_sphere(&obj->value.as_sphere, ray, res);
	else if (obj->type == PLANE)
		intersect_plane(&obj->value.as_plane, ray, res);
	else if (obj->type == CYLINDER)
		intersect_cylinder(&obj->value.as_cylinder, ray, res);
}
