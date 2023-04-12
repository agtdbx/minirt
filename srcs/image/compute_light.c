/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:20:07 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/12 12:11:29 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	incremente_intensity(t_intersect_ret *res, t_light const *light,
	float const reflection_ratio)
{
	res->intensity_r += light->intensity_r * light->brightness * reflection_ratio;
	res->intensity_g += light->intensity_g * light->brightness * reflection_ratio;
	res->intensity_b += light->intensity_b * light->brightness * reflection_ratio;
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

static bool add_diffuse_intensity(t_all *all, t_intersect_ret *res, t_light const *light,
	t_vector const *pixel_pos, float const reflection_ratio)
{
	float	intensity;
	float	distance;
	float	distance_intensity;
	float	angle_ratio;
	t_ray	ray_from_light;

	if (light->brightness == 0.0f)
		return (false);

	dup_vec(&ray_from_light.origin, &light->pos);
	dup_vec(&ray_from_light.direction, pixel_pos);
	sub_vec_vec(&ray_from_light.direction, &light->pos);

	distance = get_length_vec(&ray_from_light.direction);
	if (distance >= LIGHT_DIFFUSE_RADIUS)
		return (false);

	normalize_vec(&ray_from_light.direction);

	angle_ratio = -dot_product(&res->nrm, &ray_from_light.direction);
	if (angle_ratio < 0.0f)
		return (false);

	if (is_in_shadow(all, &ray_from_light, distance, res->id))
		return (false);

	distance_intensity = 1.0f - (distance / LIGHT_DIFFUSE_RADIUS);
	intensity = angle_ratio * distance_intensity
		* reflection_ratio;
	incremente_intensity(res, light, intensity);
	return (true);
}

static void	add_specular_intensity(t_intersect_ret *res, t_light const *light,
	t_ray *ray, t_vector const *pixel_pos, float const reflection_ratio)
{
	t_vector	reflection_direction;
	t_vector	direction_from_light;
	t_vector	tmp;
	float		angle_ratio;
	float		intensity;

	dup_vec(&direction_from_light, pixel_pos);
	sub_vec_vec(&direction_from_light, &light->pos);

	dup_vec(&tmp, &res->nrm);
	multiply_vec_number(&tmp,
		2 * dot_product(&direction_from_light, &res->nrm));

	dup_vec(&reflection_direction, &tmp);
	sub_vec_vec(&reflection_direction, &direction_from_light);

	normalize_vec(&reflection_direction);
	normalize_vec(&ray->direction);
	angle_ratio = dot_product(&ray->direction, &reflection_direction);
	if (angle_ratio <= 0.0f)
		return ;

	angle_ratio = powf(angle_ratio, res->shininess_intensity);
	intensity = angle_ratio * reflection_ratio;
	incremente_intensity(res, light, intensity);
}

void	compute_light(t_all *all, t_intersect_ret *res, t_ray *ray)
{
	float const		reflection_ambiant_light_ratio = 0.2f;
	float const		reflection_diffuse_light_ratio = 0.5f;
	float const		reflection_specular_ratio = 0.3f;
	int				i;
	t_vector const	pixel_pos = get_point_on_ray(ray, res->dst);
	bool			calculate_specular;

	incremente_intensity(res, &all->scene.ambient_light,
		reflection_ambiant_light_ratio);

	i = 0;
	while (i < 1)
	{
		calculate_specular = add_diffuse_intensity(all, res, &all->scene.light, &pixel_pos,
			reflection_diffuse_light_ratio);
		if (calculate_specular)
			add_specular_intensity(res, &all->scene.light, ray, &pixel_pos,
				reflection_specular_ratio);
		i++;
	}
}
