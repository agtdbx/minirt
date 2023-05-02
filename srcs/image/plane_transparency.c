/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_transparency.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:02:54 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/02 09:58:54 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	plane_transparency(t_all *all, t_intersect_ret *res, t_ray *ray)
{
	t_intersect_ret	transparency_res;
	t_ray			transparency_ray;

	transparency_ray.origin = get_point_on_ray(ray, res->dst);
	vec3_dup(&transparency_ray.direction, &ray->direction);
	init_intersect_ret(&transparency_res, res->reflect_limit - 1);
	do_intersections_without_id(all, &transparency_res, ray, res->id);
	if (transparency_res.dst > 0.0f)
		compute_light(all, &transparency_res, ray);
	merge_pixels(res, &transparency_res, res->transparency_intensity);
}
