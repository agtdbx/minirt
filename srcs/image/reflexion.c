/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflexion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:49:31 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/31 11:43:55 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	merge_color(t_dst_and_nrm *res, t_dst_and_nrm const *reflect_res);

void	apply_reflexion(t_all *all, t_dst_and_nrm *res,
			t_vector const *intersection_point, int reflect)
{
	t_dst_and_nrm	reflect_res;
	t_ray			reflect_ray;
	t_rtlst			*obj;

	if (res->reflexion_intensity == 0.0f)
		return ;
	dup_vec(&reflect_ray.origin, intersection_point);
	dup_vec(&reflect_ray.direction, &res->nrm);
	init_dst_and_nrm(&reflect_res);
	obj = all->scene.objects;
	while (obj)
	{
		if (obj->type == SPHERE)
			intersect_sphere(&obj->value.as_sphere, &reflect_ray, &reflect_res);
		else if (obj->type == PLANE)
			intersect_plane(&obj->value.as_plane, &reflect_ray, &reflect_res);
		else if (obj->type == CYLINDER)
			intersect_cylinder(&obj->value.as_cylinder, &reflect_ray,
				&reflect_res);
		obj = obj->next;
	}
	apply_dymamic_light(all, &reflect_res, &reflect_ray, reflect);
	apply_ambiant_light(all, &reflect_res);
	merge_color(res, &reflect_res);
}

static void	merge_color(t_dst_and_nrm *res, t_dst_and_nrm const *reflect_res)
{
	float const	inv_intensity = 1.0f - res->reflexion_intensity;

	res->color.r = (float)res->color.r * inv_intensity
		+ (float)reflect_res->color.r * res->reflexion_intensity;
	res->color.g = (float)res->color.g * inv_intensity
		+ (float)reflect_res->color.g * res->reflexion_intensity;
	res->color.b = (float)res->color.b * inv_intensity
		+ (float)reflect_res->color.b * res->reflexion_intensity;
	res->intensity_r = res->intensity_r * inv_intensity
		+ reflect_res->intensity_r * res->reflexion_intensity;
	res->intensity_g = res->intensity_g * inv_intensity
		+ reflect_res->intensity_g * res->reflexion_intensity;
	res->intensity_b = res->intensity_b * inv_intensity
		+ reflect_res->intensity_b * res->reflexion_intensity;
}
