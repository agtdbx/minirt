/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_second_cylinder.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:29:55 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/28 13:27:26 by aderouba         ###   ########.fr       */
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

// param : cylinder, ray
// result : distance beetween ray origin and cylinder.
//			if resut < 0, no interection
void	intersect_second_cylinder(t_cylinder *cylinder, t_ray *ray,
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
	dst[0] = solve_second_quadratic(abc[0], abc[1], abc[2]);
	dst[1] = dv_xv[0] * dst[0] + dv_xv[1];
	if (dst[1] <= 0.0f || dst[1] > cylinder->height)
	{
		intersect_cylinder_ends(cylinder, ray, intersect_ret);
		return ;
	}
	if (0.0f <= dst[0]
		&& dst[0] > intersect_ret->dst)
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
	intersect_ret->color = cylinder->color;
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
	interect_cylinder_top_end(cylinder, ray, intersect_ret, &dst1);
	intersect_cylinder_bot_end(cylinder, ray, intersect_ret, &dst0);
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
		&& dst1->dst > intersect_ret->dst)
	{
		intersect_ret->dst = dst1->dst;
		intersect_ret->nrm = cylinder->top.normal;
		intersect_ret->color = cylinder->color;
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
		&& dst0->dst > intersect_ret->dst)
	{
		intersect_ret->dst = dst0->dst;
		intersect_ret->nrm = cylinder->bot.normal;
		intersect_ret->color = cylinder->color;
		intersect_ret->shininess_intensity = cylinder->shininess_intensity;
		intersect_ret->reflexion_intensity = cylinder->reflexion_intensity;
		intersect_ret->transparency_intensity
			= cylinder->transparency_intensity;
		intersect_ret->refraction_intensity = cylinder->refraction_intensity;
		intersect_ret->id = cylinder->id;
	}
}
