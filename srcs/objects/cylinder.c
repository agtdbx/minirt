/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:29:55 by aderouba          #+#    #+#             */
/*   Updated: 2023/02/27 13:51:03 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	intersect_cylinder_ends(t_cylinder *cylinder, t_ray *ray,
				t_dst_and_nrm *dst_nrm);

t_cylinder	create_cylinder(t_vector origin, t_vector axis, float diameter,
				float height)
{
	t_cylinder	res;
	t_vector	rev_axis;

	rev_axis = multiply_vect_number(&axis, -1.0f);
	res.origin = origin;
	res.bot_origin = origin;
	res.bot_origin.x += rev_axis.x * (height / 2.0f);
	res.bot_origin.y += rev_axis.y * (height / 2.0f);
	res.bot_origin.z += rev_axis.z * (height / 2.0f);
	res.top_origin = origin;
	res.top_origin.x += axis.x * (height / 2.0f);
	res.top_origin.y += axis.y * (height / 2.0f);
	res.top_origin.z += axis.z * (height / 2.0f);
	res.bot = create_plane(res.bot_origin, rev_axis, 0XFFFFFFFF);
	res.top = create_plane(res.top_origin, axis, 0XFFFFFFFF);
	res.axis = axis;
	res.radius = diameter / 2.0f;
	res.radius2 = res.radius * res.radius;
	res.height = height;
	res.color = 0XFFFFFFFF;
	return (res);
}

void	set_cylinder_color(t_cylinder *cylinder, int color)
{
	cylinder->color = color;
	cylinder->bot.color = color;
	cylinder->top.color = color;
}

// param : cylinder, ray
// result : distance beetween ray origin and cylinder.
//			if resut < 0, no interection
void	intersect_cylinder(t_cylinder *cylinder, t_ray *ray,
			t_dst_and_nrm *dst_nrm)
{
	float		dst;
	float		abc[3];
	float		m;
	t_vector	x;
	float		dv_xv[2];

	x = sub_vect_vect(&ray->origin, &cylinder->bot_origin);
	dv_xv[0] = dot_product(&ray->direction, &cylinder->axis);
	dv_xv[1] = dot_product(&x, &cylinder->axis);
	abc[0] = dot_product(&ray->direction, &ray->direction)
		- (dv_xv[0] * dv_xv[0]);
	abc[1] = (dot_product(&ray->direction, &x) - (dv_xv[0] * dv_xv[1])) * 2.0f;
	abc[2] = dot_product(&x, &x) - (dv_xv[1] * dv_xv[1]) - cylinder->radius2;
	if (abc[0] == 0.0f)
	{
		intersect_cylinder_ends(cylinder, ray, dst_nrm);
		return ;
	}
	dst = solve_quadratic(abc[0], abc[1], abc[2]);
	m = dv_xv[0] * dst + dv_xv[1];
	if (m < 0 || m > cylinder->height)
		return ;
	if (0.0f <= dst && (dst_nrm->dst < 0.0f || dst < dst_nrm->dst))
		dst_nrm->dst = dst;
}

static void	intersect_cylinder_ends(t_cylinder *cylinder, t_ray *ray,
				t_dst_and_nrm *dst_nrm)
{
	t_dst_and_nrm	dst0;
	t_dst_and_nrm	dst1;
	t_vector		x;
	t_vector		p;
	float			d;

	intersect_plane(&cylinder->bot, ray, &dst0);
	intersect_plane(&cylinder->top, ray, &dst1);
	if (dst1.dst < 0.0f || (0.0f <= dst0.dst && dst0.dst <= dst1.dst))
	{
		if (dst0.dst < 0.0f)
			return ;
		p = get_point_on_ray(ray, dst0.dst);
		x = sub_vect_vect(&p, &cylinder->bot_origin);
		d = dot_product(&x, &x);
		if (d > cylinder->radius2)
			return ;
		if (0.0f <= dst0.dst && (dst_nrm->dst < 0.0f || dst0.dst < dst_nrm->dst))
			dst_nrm->dst = dst0.dst;
	}
	p = get_point_on_ray(ray, dst1.dst);
	x = sub_vect_vect(&p, &cylinder->top_origin);
	d = dot_product(&x, &x);
	if (d > cylinder->radius2)
		return ;
	if (0.0f <= dst1.dst && (dst_nrm->dst < 0.0f || dst1.dst < dst_nrm->dst))
		dst_nrm->dst = dst1.dst;
}
