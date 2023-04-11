/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular_reflexion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:49:31 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/11 16:17:04 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	merge_color(t_intersect_ret *res,
				t_intersect_ret const *reflect_res);

void	apply_specular_reflexion_old(t_all *all, t_intersect_ret *res,
			t_ray const *ray, int reflect)
{
	t_intersect_ret	reflect_res;
	t_ray			reflect_ray;
	t_vector		tmp;

	if (res->reflexion_intensity == 0.0f)
		return ;
	dup_vec(&tmp, &res->nrm);
	multiply_vec_number(&tmp, 2 * dot_product(&ray->direction, &res->nrm));
	reflect_ray.origin = get_point_on_ray(ray, res->dst - 0.001);
	dup_vec(&reflect_ray.direction, &ray->direction);
	sub_vec_vec(&reflect_ray.direction, &tmp);
	init_intersect_ret(&reflect_res);
	do_intersections(all, &reflect_res, &reflect_ray);
	apply_dymamic_light_old(all, &reflect_res, &reflect_ray, reflect);
	apply_ambiant_light_old(all, &reflect_res);
	merge_color(res, &reflect_res);
}

static void	merge_color(t_intersect_ret *res,
				t_intersect_ret const *reflect_res)
{
	float const	inv_intensity = 1.0f - res->reflexion_intensity;
	float		tmp_intensity_r;
	float		tmp_intensity_g;
	float		tmp_intensity_b;

	// res->color.r = (float)res->color.r * inv_intensity
	// 	+ (float)reflect_res->color.r * res->reflexion_intensity;
	// res->color.g = (float)res->color.g * inv_intensity
	// 	+ (float)reflect_res->color.g * res->reflexion_intensity;
	// res->color.b = (float)res->color.b * inv_intensity
	// 	+ (float)reflect_res->color.b * res->reflexion_intensity;
	tmp_intensity_r = res->intensity_r * inv_intensity
		+ reflect_res->intensity_r * res->reflexion_intensity;
	tmp_intensity_g = res->intensity_g * inv_intensity
		+ reflect_res->intensity_g * res->reflexion_intensity;
	tmp_intensity_b = res->intensity_b * inv_intensity
		+ reflect_res->intensity_b * res->reflexion_intensity;
	res->intensity_r *= tmp_intensity_r;
	res->intensity_g *= tmp_intensity_g;
	res->intensity_b *= tmp_intensity_b;
	res->intensity_r *= 2.0f;
	res->intensity_g *= 2.0f;
	res->intensity_b *= 2.0f;
}
