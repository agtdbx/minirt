/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_ligth.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:00:03 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/11 16:17:04 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static bool	is_in_shadow(t_all *all, t_ray *ray, float distance, int id_ignore);
static void	apply_ligth_effect(t_all *all, t_intersect_ret *res,
				float intensity, float distance);

void	apply_ambiant_light_old(t_all *all, t_intersect_ret *res)
{
	float	intensity_r;
	float	intensity_g;
	float	intensity_b;

	if (res->dst == -1.0f || all->scene.ambient_light.brightness == 0.0f)
		return ;
	intensity_r = all->scene.ambient_light.intensity_r
		* all->scene.ambient_light.brightness;
	intensity_g = all->scene.ambient_light.intensity_g
		* all->scene.ambient_light.brightness;
	intensity_b = all->scene.ambient_light.intensity_b
		* all->scene.ambient_light.brightness;
	if (res->intensity_r < intensity_r)
		res->intensity_r = intensity_r;
	if (res->intensity_g < intensity_g)
		res->intensity_g = intensity_g;
	if (res->intensity_b < intensity_b)
		res->intensity_b = intensity_b;
}

void	apply_dymamic_light_old(t_all *all, t_intersect_ret *res, t_ray *ray,
			int reflect)
{
	t_vector		intersection_point;
	t_ray			light_ray;
	float			intensity;
	float			distance;

	if (res->dst == -1.0f || all->scene.light.brightness == 0.0f)
		return ;
	intersection_point = get_point_on_ray(ray, res->dst);
	dup_vec(&light_ray.origin, &all->scene.light.pos);
	dup_vec(&light_ray.direction, &intersection_point);
	sub_vec_vec(&light_ray.direction, &all->scene.light.pos);
	distance = get_length_vec(&light_ray.direction);
	if (distance > LIGHT_DIFFUSE_RADIUS)
		return ;
	normalize_vec(&light_ray.direction);
	intensity = -dot_product(&res->nrm, &light_ray.direction);
	if (intensity < 0.0f)
		return ;
	if (is_in_shadow(all, &light_ray, distance, res->id))
		return ;
	apply_ligth_effect(all, res, intensity, distance);
	if (reflect > 0)
		apply_specular_reflexion_old(all, res, ray, reflect - 1);
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

static void	apply_ligth_effect(t_all *all, t_intersect_ret *res,
				float intensity, float distance)
{
	res->intensity_r = all->scene.light.intensity_r
		* all->scene.light.brightness;
	res->intensity_g = all->scene.light.intensity_g
		* all->scene.light.brightness;
	res->intensity_b = all->scene.light.intensity_b
		* all->scene.light.brightness;
	res->intensity_r *= intensity;
	res->intensity_g *= intensity;
	res->intensity_b *= intensity;
	intensity = 1.0f - (distance / LIGHT_DIFFUSE_RADIUS);
	res->intensity_r *= intensity;
	res->intensity_g *= intensity;
	res->intensity_b *= intensity;
}
