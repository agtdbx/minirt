/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:29:55 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/12 16:56:16 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	assign_result_value(t_cylinder *cylinder, t_ray *ray,
				t_intersect_ret *intersect_ret, float *dst);
static void	intersect_cylinder_ends(t_cylinder *cylinder, t_ray *ray,
				t_intersect_ret *intersect_ret);
static void	interect_cylinder_top_end(t_cylinder *cylinder, t_ray *ray,
				t_intersect_ret *intersect_ret, t_intersect_ret *dst1);
static void	intersect_cylinder_bot_end(t_cylinder *cylinder, t_ray *ray,
				t_intersect_ret *intersect_ret, t_intersect_ret *dst0);
static t_color	cylinder_map(t_vec3 const *p, t_cylinder const *cylinder,
					float cy);
static t_color	cylinder_ends_map(t_vec3 const *p, t_plane const *plane);

// param : cylinder, ray
// result : distance beetween ray origin and cylinder.
//			if resut < 0, no interection
void	intersect_cylinder(t_cylinder *cylinder, t_ray *ray,
			t_intersect_ret *intersect_ret)
{
	float	dst[2];
	float	abc[3];
	float	dv_xv[2];
	t_vec3	x;

	vec3_dup(&x, &ray->origin);
	vec3_sub_vec3(&x, &cylinder->bot_origin);
	dv_xv[0] = vec3_dot_product(&ray->direction, &cylinder->axis);
	dv_xv[1] = vec3_dot_product(&x, &cylinder->axis);
	abc[0] = vec3_dot_product(&ray->direction, &ray->direction)
		- (dv_xv[0] * dv_xv[0]);
	abc[1] = (vec3_dot_product(&ray->direction, &x) - (dv_xv[0] * dv_xv[1]))
		* 2.0f;
	abc[2] = vec3_dot_product(&x, &x) - (dv_xv[1] * dv_xv[1])
		- cylinder->radius2;
	dst[0] = solve_quadratic(abc[0], abc[1], abc[2]);
	dst[1] = dv_xv[0] * dst[0] + dv_xv[1];
	if (dst[1] <= 0.0f || dst[1] > cylinder->height)
	{
		intersect_cylinder_ends(cylinder, ray, intersect_ret);
		return ;
	}
	if (0.0f <= dst[0]
		&& (intersect_ret->dst < 0.0f || dst[0] < intersect_ret->dst))
		assign_result_value(cylinder, ray, intersect_ret, dst);
}

static void	assign_result_value(t_cylinder *cylinder, t_ray *ray,
			t_intersect_ret *intersect_ret, float *dst)
{
	t_vec3	x;

	intersect_ret->dst = dst[0];
	x = get_point_on_ray(ray, dst[0]);
	vec3_sub_vec3(&x, &cylinder->bot_origin);
	vec3_dup(&intersect_ret->nrm, &cylinder->axis);
	vec3_multiply_number(&intersect_ret->nrm, dst[1]);
	vec3_sub_vec3(&x, &intersect_ret->nrm);
	vec3_fill(&intersect_ret->nrm, x.x, x.y, x.z);
	vec3_normalize(&intersect_ret->nrm);

	// intersect_ret->color = cylinder->color;

	t_vec3	p = get_point_on_ray(ray, intersect_ret->dst);
	vec3_sub_vec3(&p, &cylinder->origin);
	intersect_ret->color = cylinder_map(&p, cylinder, dst[1]);

	intersect_ret->shininess_intensity = cylinder->shininess_intensity;
	intersect_ret->reflexion_intensity = cylinder->reflexion_intensity;
	intersect_ret->transparency_intensity = cylinder->transparency_intensity;
	intersect_ret->refraction_intensity = cylinder->refraction_intensity;
	intersect_ret->id = cylinder->id;
	intersect_cylinder_ends(cylinder, ray, intersect_ret);
}

static void	intersect_cylinder_ends(t_cylinder *cylinder, t_ray *ray,
				t_intersect_ret *intersect_ret)
{
	t_intersect_ret	dst0;
	t_intersect_ret	dst1;

	dst0.dst = -1.0f;
	vec3_fill(&dst0.nrm, 0.0f, 0.0f, 0.0f);
	dst1.dst = -1.0f;
	vec3_fill(&dst1.nrm, 0.0f, 0.0f, 0.0f);
	intersect_plane(&cylinder->bot, ray, &dst0);
	intersect_plane(&cylinder->top, ray, &dst1);
	if (dst0.dst < 0.0f && dst1.dst < 0.0f)
		return ;
	if (dst0.dst < 0.0f)
		interect_cylinder_top_end(cylinder, ray, intersect_ret, &dst1);
	if (dst1.dst < 0.0f)
		intersect_cylinder_bot_end(cylinder, ray, intersect_ret, &dst0);
	if (dst0.dst < dst1.dst)
		intersect_cylinder_bot_end(cylinder, ray, intersect_ret, &dst0);
	else
		interect_cylinder_top_end(cylinder, ray, intersect_ret, &dst1);
}

static void	interect_cylinder_top_end(t_cylinder *cylinder, t_ray *ray,
				t_intersect_ret *intersect_ret, t_intersect_ret *dst1)
{
	t_vec3	x;
	t_vec3	p;
	float	d;

	if (dst1->dst < 0.0f)
		return ;
	p = get_point_on_ray(ray, dst1->dst);
	vec3_dup(&x, &p);
	vec3_sub_vec3(&x, &cylinder->top_origin);
	d = vec3_dot_product(&x, &x);
	if (d > cylinder->radius2)
		return ;
	if (0.0f <= dst1->dst
		&& (intersect_ret->dst <= 0.0f || dst1->dst < intersect_ret->dst))
	{
		intersect_ret->dst = dst1->dst;
		intersect_ret->nrm = cylinder->top.normal;

		// intersect_ret->color = cylinder->color;

		t_vec3	p = get_point_on_ray(ray, intersect_ret->dst);
		vec3_sub_vec3(&p, &cylinder->origin);
		intersect_ret->color = cylinder_ends_map(&p, &cylinder->top);

		intersect_ret->shininess_intensity = cylinder->shininess_intensity;
		intersect_ret->reflexion_intensity = cylinder->reflexion_intensity;
		intersect_ret->transparency_intensity
			= cylinder->transparency_intensity;
		intersect_ret->refraction_intensity = cylinder->refraction_intensity;
		intersect_ret->id = cylinder->id;
	}
}

static void	intersect_cylinder_bot_end(t_cylinder *cylinder, t_ray *ray,
				t_intersect_ret *intersect_ret, t_intersect_ret *dst0)
{
	t_vec3	x;
	t_vec3	p;
	float	d;

	if (dst0->dst < 0.0f)
		return ;
	p = get_point_on_ray(ray, dst0->dst);
	vec3_dup(&x, &p);
	vec3_sub_vec3(&x, &cylinder->bot_origin);
	d = vec3_dot_product(&x, &x);
	if (d > cylinder->radius2)
		return ;
	if (0.0f <= dst0->dst
		&& (intersect_ret->dst <= 0.0f || dst0->dst < intersect_ret->dst))
	{
		intersect_ret->dst = dst0->dst;
		intersect_ret->nrm = cylinder->bot.normal;

		// intersect_ret->color = cylinder->color;

		t_vec3	p = get_point_on_ray(ray, intersect_ret->dst);
		vec3_sub_vec3(&p, &cylinder->origin);
		intersect_ret->color = cylinder_ends_map(&p, &cylinder->bot);

		intersect_ret->shininess_intensity = cylinder->shininess_intensity;
		intersect_ret->reflexion_intensity = cylinder->reflexion_intensity;
		intersect_ret->transparency_intensity
			= cylinder->transparency_intensity;
		intersect_ret->refraction_intensity = cylinder->refraction_intensity;
		intersect_ret->id = cylinder->id;
	}
}

static t_color	do_checkboard(float w, float h, float u, float v)
{
	t_color	res;

	res.r = 0;
	res.g = 0;
	res.b = 0;

	if (((int)(u * w) + (int)(v * h)) % 2)
	{
		res.r = 255;
		res.g = 255;
		res.b = 255;
	}
	return (res);
}

// static void	align_on_y(t_vec3 *rp, t_vec3 const *axis)
// {
// 	float	xy_length;
// 	float	z_angle;
// 	float	vec_length;
// 	float	x_angle;

// 	xy_length = sqrtf((axis->x * axis->x) + (axis->y * axis->y));
// 	if (xy_length == 0.0f)
// 	{
// 		z_angle = 90 * DIV_180_BY_PI;
// 		if (axis->x < 0.0f)
// 			z_angle = -z_angle;
// 	}
// 	else
// 		z_angle = acosf(axis->y / xy_length);

// 	vec_length = vec3_get_length(axis);
// 	x_angle = acosf(xy_length / vec_length);
// 	if (axis->z < 0.0f)
// 		x_angle = -x_angle;
// 	else if (axis->z == 0.0f)
// 		x_angle = 0.0f;
// 	if (axis->x > 0.0f)
// 		z_angle = -z_angle;
// 	else if (axis->x == 0.0f)
// 		z_angle = 0.0f;

// 	t_vec3	xy_axis[2];
// 	get_screen_basis(axis, xy_axis, 1);

// 	vec3_normalize(&xy_axis[0]);
// 	vec3_normalize(&xy_axis[1]);

// 	absolute_rotate_rad(rp, x_angle, ROTATE_AROUND_X);
// 	absolute_rotate_rad(rp, z_angle, ROTATE_AROUND_Z);
// 	// relative_rotate(rp, &xy_axis[0], z_angle);

// }

static t_color	cylinder_map(t_vec3 const *p, t_cylinder const *cylinder,
					float cy)
{
	t_vec3	ref; // vecteur de référence parallèle à Oxz (le sol)
	t_vec3	tmp;
	t_vec3	proj; // projeté de p sur le plan normal à axis
	float	cx;

	if (cylinder->axis.x != 0.0f || cylinder->axis.y != 0.0f)
		vec3_fill(&ref, -cylinder->axis.y, cylinder->axis.x, 0.0f);
	else
		vec3_fill(&ref, 0.0f, 0.0f, 1.0f);

	vec3_cross_product(&cylinder->axis, p, &tmp);
	vec3_cross_product(&cylinder->axis, &tmp, &proj);
	vec3_normalize(&ref);
	vec3_normalize(&proj);

	cx = acosf(vec3_dot_product(&proj, &ref));

	cx = cx / (2.0f * PI);

	vec3_cross_product(&cylinder->axis, &ref, &tmp);
	vec3_normalize(&tmp);
	if (vec3_dot_product(&proj, &tmp) < 0.0f)
		cx = 1.0f - cx;

	cy /= cylinder->height;

	return (do_checkboard(8.0f, 8.0f, cx, cy));
}

static t_color	cylinder_ends_map(t_vec3 const *p, t_plane const *plane)
{
	float	u;
	float	v;

	t_vec3	o_x;
	t_vec3	o_y;

	if (plane->normal.x != 0.0f || plane->normal.y != 0.0f)
		vec3_fill(&o_y, -plane->normal.y, plane->normal.x, 0.0f);
	else
		vec3_fill(&o_y, 0.0f, 0.0f, 1.0f);
	vec3_cross_product(&plane->normal, &o_y, &o_x);

	vec3_normalize(&o_x);
	vec3_normalize(&o_y);

	u = vec3_dot_product(&o_x, p);
	v = vec3_dot_product(&o_y, p);
	u -= (int)u;
	v -= (int)v;
	u = (u + 1.0f) / 2.0f;
	v = (v + 1.0f) / 2.0f;
	return (do_checkboard(8.0f, 8.0f, u, v));
}
