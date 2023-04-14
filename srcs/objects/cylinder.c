/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:29:55 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/13 12:13:33 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	assign_result_value(t_cylinder *cylinder, t_ray *ray,
				t_intersect_ret *intersect_ret, float *dst);
static void	intersect_cylinder_ends(t_cylinder *cylinder, t_ray *ray,
				t_intersect_ret *intersect_ret);
static void	intersect_cylinder_bot_end(t_cylinder *cylinder, t_ray *ray,
				t_intersect_ret *intersect_ret, t_intersect_ret *dst0);

t_cylinder	create_cylinder(t_vector origin, t_vector axis, float size[2],
				t_color color)
{
	t_cylinder	res;
	t_vector	rev_axis;

	dup_vec(&rev_axis, &axis);
	multiply_vec_number(&rev_axis, -1.0f);
	res.radius = size[0] / 2.0f;
	res.radius2 = res.radius * res.radius;
	res.height = size[1];
	dup_vec(&res.origin, &origin);
	dup_vec(&res.bot_origin, &origin);
	res.bot_origin.x += rev_axis.x * (res.height / 2.0f);
	res.bot_origin.y += rev_axis.y * (res.height / 2.0f);
	res.bot_origin.z += rev_axis.z * (res.height / 2.0f);
	dup_vec(&res.top_origin, &origin);
	res.top_origin.x += axis.x * (res.height / 2.0f);
	res.top_origin.y += axis.y * (res.height / 2.0f);
	res.top_origin.z += axis.z * (res.height / 2.0f);
	res.bot = create_plane(res.bot_origin, rev_axis, color);
	res.top = create_plane(res.top_origin, axis, color);
	dup_vec(&res.axis, &axis);
	res.color = color;
	res.id = -1;
	res.shininess_intensity = 10.0f;
	res.reflexion_intensity = 0.0f;
	return (res);
}

// param : cylinder, ray
// result : distance beetween ray origin and cylinder.
//			if resut < 0, no interection
void	intersect_cylinder(t_cylinder *cylinder, t_ray *ray,
			t_intersect_ret *intersect_ret)
{
	float		dst[2];
	float		abc[3];
	float		dv_xv[2];
	t_vector	x;

	dup_vec(&x, &ray->origin);
	sub_vec_vec(&x, &cylinder->bot_origin);
	dv_xv[0] = dot_product(&ray->direction, &cylinder->axis);
	dv_xv[1] = dot_product(&x, &cylinder->axis);
	abc[0] = dot_product(&ray->direction, &ray->direction)
		- (dv_xv[0] * dv_xv[0]);
	abc[1] = (dot_product(&ray->direction, &x) - (dv_xv[0] * dv_xv[1])) * 2.0f;
	abc[2] = dot_product(&x, &x) - (dv_xv[1] * dv_xv[1]) - cylinder->radius2;
	dst[0] = solve_quadratic(abc[0], abc[1], abc[2]);
	dst[1] = dv_xv[0] * dst[0] + dv_xv[1];
	if (dst[1] < 0 || dst[1] > cylinder->height)
	{
		intersect_cylinder_ends(cylinder, ray, intersect_ret);
		return ;
	}
	if (0.0f <= dst[0] && (intersect_ret->dst < 0.0f || dst[0] < intersect_ret->dst))
		assign_result_value(cylinder, ray, intersect_ret, dst);
}

static void	assign_result_value(t_cylinder *cylinder, t_ray *ray,
			t_intersect_ret *intersect_ret, float *dst)
{
	t_vector	x;

	intersect_ret->dst = dst[0];
	x = get_point_on_ray(ray, dst[0]);
	sub_vec_vec(&x, &cylinder->bot_origin);
	dup_vec(&intersect_ret->nrm, &cylinder->axis);
	multiply_vec_number(&intersect_ret->nrm, dst[1]);
	sub_vec_vec(&x, &intersect_ret->nrm);
	fill_vec(&intersect_ret->nrm, x.x, x.y, x.z);
	normalize_vec(&intersect_ret->nrm);
	intersect_ret->color = cylinder->color;
	intersect_ret->shininess_intensity = cylinder->shininess_intensity;
	intersect_ret->reflexion_intensity = cylinder->reflexion_intensity;
	intersect_ret->id = cylinder->id;
}

static void	intersect_cylinder_ends(t_cylinder *cylinder, t_ray *ray,
				t_intersect_ret *intersect_ret)
{
	t_intersect_ret	dst0;
	t_intersect_ret	dst1;
	t_vector		x;
	t_vector		p;
	float			d;

	dst0.dst = -1.0f;
	fill_vec(&dst0.nrm, 0.0f, 0.0f, 0.0f);
	dst1.dst = -1.0f;
	fill_vec(&dst1.nrm, 0.0f, 0.0f, 0.0f);
	intersect_plane(&cylinder->bot, ray, &dst0);
	intersect_plane(&cylinder->top, ray, &dst1);
	if (dst1.dst < 0.0f || (0.0f <= dst0.dst && dst0.dst <= dst1.dst))
		intersect_cylinder_bot_end(cylinder, ray, intersect_ret, &dst0);
	p = get_point_on_ray(ray, dst1.dst);
	dup_vec(&x, &p);
	sub_vec_vec(&x, &cylinder->top_origin);
	d = dot_product(&x, &x);
	if (d > cylinder->radius2)
		return ;
	if (0.0f <= dst1.dst && (intersect_ret->dst <= 0.0f || dst1.dst < intersect_ret->dst))
	{
		intersect_ret->dst = dst1.dst;
		intersect_ret->nrm = cylinder->top.normal;
		intersect_ret->color = cylinder->color;
		intersect_ret->shininess_intensity = cylinder->shininess_intensity;
		intersect_ret->reflexion_intensity = cylinder->reflexion_intensity;
		intersect_ret->id = cylinder->id;
	}
}

static void	intersect_cylinder_bot_end(t_cylinder *cylinder, t_ray *ray,
				t_intersect_ret *intersect_ret, t_intersect_ret *dst0)
{
	t_vector	x;
	t_vector	p;
	float		d;

	if (dst0->dst < 0.0f)
		return ;
	p = get_point_on_ray(ray, dst0->dst);
	dup_vec(&x, &p);
	sub_vec_vec(&x, &cylinder->bot_origin);
	d = dot_product(&x, &x);
	if (d > cylinder->radius2)
		return ;
	if (0.0f <= dst0->dst
		&& (intersect_ret->dst <= 0.0f || dst0->dst < intersect_ret->dst))
	{
		intersect_ret->dst = dst0->dst;
		intersect_ret->nrm = cylinder->bot.normal;
		intersect_ret->color = cylinder->color;
		intersect_ret->shininess_intensity = cylinder->shininess_intensity;
		intersect_ret->reflexion_intensity = cylinder->reflexion_intensity;
		intersect_ret->id = cylinder->id;
	}
}
