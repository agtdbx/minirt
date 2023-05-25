/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_second_cone.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:38:03 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/25 12:49:57 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	assign_second_result_value(t_cone * cone, t_intersect_ret *ret,
				t_ray *ray, float dst, float m, float tmp);
static void	intersect_second_end(t_cone *cone, t_ray *ray,
				t_intersect_ret *ret);


void	intersect_second_cone(t_cone *cone, t_ray *ray,
			t_intersect_ret *ret)
{
	float const	k = cone->radius / cone->height;
	float		m;
	float		a;
	float		b;
	float		c;
	float		dst;
	float		tmp;
	float		d_dot_v;
	float		x_dot_v;
	t_vec3		x;

	// Precalculate of X
	vec3_dup(&x, &ray->origin);
	vec3_sub_vec3(&x, &cone->origin);

	tmp = 1.0f + k * k;
	d_dot_v = vec3_dot_product(&ray->direction, &cone->axis);
	x_dot_v = vec3_dot_product(&x, &cone->axis);

	// Calculate of a b c
	a = vec3_dot_product(&ray->direction, &ray->direction)
		- tmp * (d_dot_v * d_dot_v);
	b = vec3_dot_product(&ray->direction, &x) - tmp * (d_dot_v * x_dot_v);
	b *= 2.0f;
	c = vec3_dot_product(&x, &x) - tmp * (x_dot_v * x_dot_v);

	// Calculate dist
	dst = solve_second_quadratic(a, b, c);
	m = d_dot_v * dst + x_dot_v;
	if (m < 0.0f || m > cone->height)
	{
		intersect_second_end(cone, ray, ret);
		return ;
	}
	if (0.0f <= dst && dst > ret->dst)
		assign_second_result_value(cone, ret, ray, dst, m, tmp);
}

static void	assign_second_result_value(t_cone * cone, t_intersect_ret *ret,
				t_ray *ray, float dst, float m, float tmp)
{
	t_vec3	tmp_vec;

	ret->dst = dst;
	// calculate normal
	ret->nrm = get_point_on_ray(ray, dst);
	vec3_sub_vec3(&ret->nrm, &cone->origin);
	vec3_dup(&tmp_vec, &cone->axis);
	vec3_multiply_number(&tmp_vec, tmp * m);
	vec3_sub_vec3(&ret->nrm, &tmp_vec);
	vec3_normalize(&ret->nrm);

	ret->shininess_intensity = cone->shininess_intensity;
	ret->reflexion_intensity = cone->reflexion_intensity;
	ret->transparency_intensity = cone->transparency_intensity;
	ret->refraction_intensity = cone->refraction_intensity;
	ret->id = cone->id;
	ret->color = cone->color;
	intersect_second_end(cone, ray, ret);
}

static void	intersect_second_end(t_cone *cone, t_ray *ray,
				t_intersect_ret *ret)
{
	t_intersect_ret	tmp;
	t_vec3			x;
	float			d;

	init_intersect_ret(&tmp, 0);
	intersect_plane(&cone->end, ray, &tmp);
	if (tmp.dst < 0.0f)
		return ;
	x = get_point_on_ray(ray, tmp.dst);
	vec3_sub_vec3(&x, &cone->end_pos);
	d = vec3_dot_product(&x, &x);
	if (d > cone->radius2)
		return ;
	if (0.0f <= tmp.dst && tmp.dst > ret->dst)
	{
		ret->dst = tmp.dst;
		ret->nrm = cone->end.normal;
		ret->color = cone->color;
		ret->shininess_intensity = cone->shininess_intensity;
		ret->reflexion_intensity = cone->reflexion_intensity;
		ret->transparency_intensity = cone->transparency_intensity;
		ret->refraction_intensity = cone->refraction_intensity;
		ret->id = cone->id;
	}
}
