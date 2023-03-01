/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:29:55 by aderouba          #+#    #+#             */
/*   Updated: 2023/02/28 14:32:22 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	assign_result_value(t_cylinder *cylinder, t_ray *ray,
				t_dst_and_nrm *dst_nrm, float *dst);
static void	intersect_cylinder_ends(t_cylinder *cylinder, t_ray *ray,
				t_dst_and_nrm *dst_nrm);
static void	intersect_cylinder_bot_end(t_cylinder *cylinder, t_ray *ray,
				t_dst_and_nrm *dst_nrm, t_dst_and_nrm *dst0);

t_cylinder	create_cylinder(t_vector origin, t_vector axis, float *size,
				int color)
{
	t_cylinder	res;
	t_vector	rev_axis;

	rev_axis = multiply_vect_number(&axis, -1.0f);
	res.radius = size[0] / 2.0f;
	res.radius2 = res.radius * res.radius;
	res.height = size[1];
	res.origin = origin;
	res.bot_origin = origin;
	res.bot_origin.x += rev_axis.x * (res.height / 2.0f);
	res.bot_origin.y += rev_axis.y * (res.height / 2.0f);
	res.bot_origin.z += rev_axis.z * (res.height / 2.0f);
	res.top_origin = origin;
	res.top_origin.x += axis.x * (res.height / 2.0f);
	res.top_origin.y += axis.y * (res.height / 2.0f);
	res.top_origin.z += axis.z * (res.height / 2.0f);
	res.bot = create_plane(res.bot_origin, rev_axis, color);
	res.top = create_plane(res.top_origin, axis, color);
	res.axis = axis;
	res.color = color;
	return (res);
}

// param : cylinder, ray
// result : distance beetween ray origin and cylinder.
//			if resut < 0, no interection
void	intersect_cylinder(t_cylinder *cylinder, t_ray *ray,
			t_dst_and_nrm *dst_nrm)
{
	float		dst[2];
	float		abc[3];
	t_vector	x;
	float		dv_xv[2];

	x = sub_vect_vect(&ray->origin, &cylinder->bot_origin);
	dv_xv[0] = dot_product(&ray->direction, &cylinder->axis);
	dv_xv[1] = dot_product(&x, &cylinder->axis);
	abc[0] = dot_product(&ray->direction, &ray->direction)
		- (dv_xv[0] * dv_xv[0]);
	if (abc[0] == 0.0f)
	{
		intersect_cylinder_ends(cylinder, ray, dst_nrm);
		return ;
	}
	abc[1] = (dot_product(&ray->direction, &x) - (dv_xv[0] * dv_xv[1])) * 2.0f;
	abc[2] = dot_product(&x, &x) - (dv_xv[1] * dv_xv[1]) - cylinder->radius2;
	dst[0] = solve_quadratic(abc[0], abc[1], abc[2]);
	dst[1] = dv_xv[0] * dst[0] + dv_xv[1];
	if (dst[1] < 0 || dst[1] > cylinder->height)
		return ;
	if (0.0f <= dst[0] && (dst_nrm->dst < 0.0f || dst[0] < dst_nrm->dst))
		assign_result_value(cylinder, ray, dst_nrm, dst);
}

static void	assign_result_value(t_cylinder *cylinder, t_ray *ray,
			t_dst_and_nrm *dst_nrm, float *dst)
{
	t_vector	x;

	dst_nrm->dst = dst[0];
	x = get_point_on_ray(ray, dst[0]);
	x = sub_vect_vect(&x, &cylinder->bot_origin);
	dst_nrm->nrm = multiply_vect_number(&cylinder->axis, dst[1]);
	x = sub_vect_vect(&x, &dst_nrm->nrm);
	dst_nrm->nrm = create_vector(x.x, x.y, x.z, true);
}

static void	intersect_cylinder_ends(t_cylinder *cylinder, t_ray *ray,
				t_dst_and_nrm *dst_nrm)
{
	t_dst_and_nrm	dst0;
	t_dst_and_nrm	dst1;
	t_vector		x;
	t_vector		p;
	float			d;

	dst0.dst = -1.0f;
	dst0.nrm = create_vector(0.0f, 0.0f, 0.0f, false);
	dst1.dst = -1.0f;
	dst1.nrm = create_vector(0.0f, 0.0f, 0.0f, false);
	intersect_plane(&cylinder->bot, ray, &dst0);
	intersect_plane(&cylinder->top, ray, &dst1);
	if (dst1.dst < 0.0f || (0.0f <= dst0.dst && dst0.dst <= dst1.dst))
		intersect_cylinder_bot_end(cylinder, ray, dst_nrm, &dst0);
	p = get_point_on_ray(ray, dst1.dst);
	x = sub_vect_vect(&p, &cylinder->top_origin);
	d = dot_product(&x, &x);
	if (d > cylinder->radius2)
		return ;
	if (0.0f <= dst1.dst && (dst_nrm->dst < 0.0f || dst1.dst < dst_nrm->dst))
	{
		dst_nrm->dst = dst1.dst;
		dst_nrm->nrm = cylinder->top.normal;
	}
}

static void	intersect_cylinder_bot_end(t_cylinder *cylinder, t_ray *ray,
				t_dst_and_nrm *dst_nrm, t_dst_and_nrm *dst0)
{
	t_vector	x;
	t_vector	p;
	float		d;

	if (dst0->dst < 0.0f)
		return ;
	p = get_point_on_ray(ray, dst0->dst);
	x = sub_vect_vect(&p, &cylinder->bot_origin);
	d = dot_product(&x, &x);
	if (d > cylinder->radius2)
		return ;
	if (0.0f <= dst0->dst
		&& (dst_nrm->dst < 0.0f || dst0->dst < dst_nrm->dst))
	{
		dst_nrm->dst = dst0->dst;
		dst_nrm->nrm = cylinder->bot.normal;
	}
}
