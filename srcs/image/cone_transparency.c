/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_transparency.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:05:21 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/25 12:55:39 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	calculate_out_ray(t_ray *refraction_ray, t_ray *transparency_ray,
				t_intersect_ret *refraction_res, t_cone *cone);
static void	cone_reflect(t_ray *refraction_ray, t_ray *transparency_ray,
				t_intersect_ret *refraction_res, t_cone *cone);
static void	intern_reflect(t_ray *refraction_ray,
				t_intersect_ret *refraction_res);

void	cone_transparency(t_all *all, t_intersect_ret *res, t_ray *ray,
			t_cone *cone)
{
	t_intersect_ret	refraction_res;
	t_intersect_ret	transparency_res;
	t_ray			refraction_ray;
	t_ray			transparency_ray;
	float			ni_over_nt;

	refraction_ray.origin = get_point_on_ray(ray, res->dst);
	ni_over_nt = 1.0f / res->refraction_intensity;
	if (refract(&ray->direction, &res->nrm, ni_over_nt,
			&refraction_ray.direction) == false)
	{
		transparency_reflect(all, res, ray);
		return ;
	}
	init_intersect_ret(&refraction_res, res->reflect_limit - 1);
	intersect_second_cone(cone, &refraction_ray, &refraction_res);
	if (refraction_res.dst < 0.0f)
	{
		// printf("wait\n");
		// return ;
		refraction_res.dst = 0.0f;
	}
	calculate_out_ray(&refraction_ray, &transparency_ray, &refraction_res,
		cone);
	init_intersect_ret(&transparency_res, res->reflect_limit - 1);
	do_intersections_without_id(all, &transparency_res, &transparency_ray,
		res->id);
	compute_light(all, &transparency_res, &transparency_ray);
	merge_pixels(res, &transparency_res, res->transparency_intensity);
}

static void	calculate_out_ray(t_ray *refraction_ray, t_ray *transparency_ray,
				t_intersect_ret *refraction_res, t_cone *cone)
{
	float const	ni_over_nt = cone->refraction_intensity;

	transparency_ray->origin = get_point_on_ray(refraction_ray,
			refraction_res->dst);
	vec3_multiply_number(&refraction_res->nrm, -1.0f);
	if (refract(&refraction_ray->direction, &refraction_res->nrm, ni_over_nt,
			&transparency_ray->direction) == false)
		cone_reflect(refraction_ray, transparency_ray, refraction_res,
			cone);

}

static void	cone_reflect(t_ray *refraction_ray, t_ray *transparency_ray,
				t_intersect_ret *refraction_res, t_cone *cone)
{
	float const	ni_over_nt = cone->refraction_intensity;
	int const	reflect_limit = refraction_res->reflect_limit;
	int			loop_limit;

	loop_limit = 10;
	while (loop_limit > 0)
	{
		intern_reflect(refraction_ray, refraction_res);
		init_intersect_ret(refraction_res, reflect_limit);
		intersect_second_cone(cone, refraction_ray, refraction_res);
		vec3_multiply_number(&refraction_res->nrm, -1.0f);
		if (refraction_res->dst >= 0.0f && refract(&refraction_ray->direction,
				&refraction_res->nrm, ni_over_nt, &transparency_ray->direction))
			break ;
		loop_limit--;
	}
}

static void	intern_reflect(t_ray *refraction_ray,
				t_intersect_ret *refraction_res)
{
	t_ray	tmp_ray;
	t_vec3	tmp;

	vec3_dup(&tmp_ray.origin, &refraction_ray->origin);
	vec3_dup(&tmp_ray.direction, &refraction_ray->direction);
	refraction_ray->origin = get_point_on_ray(&tmp_ray,
			refraction_res->dst);
	vec3_dup(&tmp, &refraction_res->nrm);
	vec3_multiply_number(&tmp,
		2 * vec3_dot_product(&tmp_ray.direction, &refraction_res->nrm));
	vec3_dup(&refraction_ray->direction, &tmp_ray.direction);
	vec3_sub_vec3(&refraction_ray->direction, &tmp);
}
