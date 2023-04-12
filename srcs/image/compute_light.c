/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:20:07 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/12 14:39:04 by aderouba         ###   ########.fr       */
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
	t_ray const *ray, t_vector const *pixel_pos, float const reflection_ratio)
{
	t_vector	reflection_direction;
	t_vector	direction_from_light;
	t_vector	tmp;
	float		angle_ratio;
	float		intensity;

	if (res->shininess_intensity == 0.0f)
		return ;

	dup_vec(&direction_from_light, pixel_pos);
	sub_vec_vec(&direction_from_light, &light->pos);

	dup_vec(&tmp, &res->nrm);
	multiply_vec_number(&tmp,
		2 * dot_product(&direction_from_light, &res->nrm));

	dup_vec(&reflection_direction, &tmp);
	sub_vec_vec(&reflection_direction, &direction_from_light);

	dup_vec(&tmp, &ray->direction);
	normalize_vec(&reflection_direction);
	normalize_vec(&tmp);
	angle_ratio = dot_product(&tmp, &reflection_direction);
	if (angle_ratio <= 0.0f)
		return ;

	angle_ratio = powf(angle_ratio, res->shininess_intensity);
	intensity = angle_ratio * reflection_ratio;
	incremente_intensity(res, light, intensity);
}

static void	do_intersections_without_id(t_all *all, t_intersect_ret *res, t_ray *ray, int id_ignore)
{
	t_rtlst	*obj;

	obj = all->scene.objects;
	while (obj)
	{
		if (obj->id != id_ignore)
		{
			if (obj->type == SPHERE)
				intersect_sphere(&obj->value.as_sphere, ray, res);
			else if (obj->type == PLANE)
				intersect_plane(&obj->value.as_plane, ray, res);
			else if (obj->type == CYLINDER)
				intersect_cylinder(&obj->value.as_cylinder, ray,
					res);
		}
		obj = obj->next;
	}
}

static void	mirror_reflection(t_all *all, t_intersect_ret *res,
			t_ray const *ray, int reflect)
{
	t_intersect_ret	mirror_res;
	t_ray			mirror_ray;
	t_vector		tmp;
	float const		inv_intensity = (1.0f - res->reflexion_intensity);

	if (res->reflexion_intensity == 0.0f
		|| res->intensity_r + res->intensity_g + res->intensity_b == 0.0f)
		return ;
	dup_vec(&tmp, &res->nrm);
	multiply_vec_number(&tmp, 2 * dot_product(&ray->direction, &res->nrm));
	mirror_ray.origin = get_point_on_ray(ray, res->dst);
	dup_vec(&mirror_ray.direction, &ray->direction);
	sub_vec_vec(&mirror_ray.direction, &tmp);

	init_intersect_ret(&mirror_res);
	do_intersections_without_id(all, &mirror_res, &mirror_ray, res->id);

	compute_light(all, &mirror_res, &mirror_ray, reflect);

	res->color.r = (float)res->color.r * inv_intensity
		+ (float)mirror_res.color.r * res->reflexion_intensity;
	res->color.g = (float)res->color.g * inv_intensity
		+ (float)mirror_res.color.g * res->reflexion_intensity;
	res->color.b = (float)res->color.b * inv_intensity
		+ (float)mirror_res.color.b * res->reflexion_intensity;

	res->intensity_r = res->intensity_r * inv_intensity
		+ mirror_res.intensity_r * res->reflexion_intensity;
	res->intensity_g = res->intensity_g * inv_intensity
		+ mirror_res.intensity_g * res->reflexion_intensity;
	res->intensity_b = res->intensity_b * inv_intensity
		+ mirror_res.intensity_b * res->reflexion_intensity;
}

void	compute_light(t_all *all, t_intersect_ret *res, t_ray *ray, int reflect)
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
		if (calculate_specular && reflect == MAX_REFLECT)
			add_specular_intensity(res, &all->scene.light, ray, &pixel_pos,
				reflection_specular_ratio);
		i++;
	}
	if (reflect > 0)
		mirror_reflection(all, res, ray, reflect - 1);
}
