/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mirror_reflection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:25:03 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/14 11:39:45 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	do_intersections_without_id(t_all *all, t_intersect_ret *res,
				t_ray *ray, int id_ignore);
static void	merge_pixels(t_intersect_ret *res, t_intersect_ret *mirror_res);

void	mirror_reflection(t_all *all, t_intersect_ret *res,
			t_ray const *ray, int reflect)
{
	t_intersect_ret	mirror_res;
	t_ray			mirror_ray;
	t_vector		tmp;

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
	merge_pixels(res, &mirror_res);
}

static void	do_intersections_without_id(t_all *all, t_intersect_ret *res,
				t_ray *ray, int id_ignore)
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

static void	merge_pixels(t_intersect_ret *res, t_intersect_ret *mirror_res)
{
	float const		inv_intensity = (1.0f - res->reflexion_intensity);

	res->color.r = (float)res->color.r * inv_intensity
		+ (float)mirror_res->color.r * res->reflexion_intensity;
	res->color.g = (float)res->color.g * inv_intensity
		+ (float)mirror_res->color.g * res->reflexion_intensity;
	res->color.b = (float)res->color.b * inv_intensity
		+ (float)mirror_res->color.b * res->reflexion_intensity;
	res->intensity_r = res->intensity_r * inv_intensity
		+ mirror_res->intensity_r * res->reflexion_intensity;
	res->intensity_g = res->intensity_g * inv_intensity
		+ mirror_res->intensity_g * res->reflexion_intensity;
	res->intensity_b = res->intensity_b * inv_intensity
		+ mirror_res->intensity_b * res->reflexion_intensity;
}
