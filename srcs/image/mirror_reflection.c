/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mirror_reflection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:25:03 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/02 10:01:22 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	mirror_reflection(t_all *all, t_intersect_ret *res,
			t_ray const *ray)
{
	t_intersect_ret	mirror_res;
	t_ray			mirror_ray;
	t_vec3			tmp;

	if (res->reflexion_intensity == 0.0f
		|| res->intensity_r + res->intensity_g + res->intensity_b == 0.0f)
		return ;
	vec3_dup(&tmp, &res->nrm);
	vec3_multiply_number(&tmp,
		2 * vec3_dot_product(&ray->direction, &res->nrm));
	mirror_ray.origin = get_point_on_ray(ray, res->dst);
	vec3_dup(&mirror_ray.direction, &ray->direction);
	vec3_sub_vec3(&mirror_ray.direction, &tmp);
	init_intersect_ret(&mirror_res, res->reflect_limit - 1);
	do_intersections_without_id(all, &mirror_res, &mirror_ray, res->id);
	mirror_res.reflect_limit = res->reflect_limit;
	compute_light(all, &mirror_res, &mirror_ray);
	merge_pixels(res, &mirror_res, res->reflexion_intensity);
}
