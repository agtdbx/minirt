/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:47:41 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/12 14:51:37 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	set_intensities_res(t_sphere *sphere,
				t_intersect_ret *intersect_ret);
static t_color	sphere_map(t_vec3 const *p);

t_sphere	create_sphere(t_vec3 origin, float diameter, t_color color)
{
	t_sphere	res;

	res.origin = origin;
	res.radius = diameter / 2.0f;
	res.radius2 = res.radius * res.radius;
	res.color = color;
	res.id = -1;
	res.shininess_intensity = 10.0f;
	res.reflexion_intensity = 0.0f;
	res.transparency_intensity = 0.0f;
	res.refraction_intensity = 1.0f;
	return (res);
}

// param : sphere, ray
// result : distance beetween ray origin and sphere.
//			if resut < 0, no interection
void	intersect_sphere(t_sphere *sphere, t_ray *ray,
			t_intersect_ret *intersect_ret)
{
	float	dst;
	float	a;
	float	b;
	float	c;
	t_vec3	x;

	vec3_dup(&x, &ray->origin);
	vec3_sub_vec3(&x, &sphere->origin);
	a = vec3_dot_product(&ray->direction, &ray->direction);
	b = 2.0f * vec3_dot_product(&ray->direction, &x);
	c = vec3_dot_product(&x, &x) - sphere->radius2;
	dst = solve_quadratic(a, b, c);
	if (0.0f <= dst && (intersect_ret->dst < 0.0f || dst < intersect_ret->dst))
	{
		intersect_ret->dst = dst;
		intersect_ret->nrm = get_point_on_ray(ray, dst);
		vec3_dup(&x, &intersect_ret->nrm);
		vec3_sub_vec3(&x, &sphere->origin);
		vec3_fill(&intersect_ret->nrm, x.x, x.y, x.z);
		vec3_normalize(&intersect_ret->nrm);

		intersect_ret->color = sphere->color;

		// t_vec3	p = get_point_on_ray(ray, dst);
		// vec3_sub_vec3(&p, &sphere->origin);
		// intersect_ret->color = sphere_map(&p);

		set_intensities_res(sphere, intersect_ret);
		intersect_ret->id = sphere->id;
	}
}

void	intersect_second_sphere(t_sphere *sphere, t_ray *ray,
			t_intersect_ret *intersect_ret)
{
	float	dst;
	float	a;
	float	b;
	float	c;
	t_vec3	x;

	vec3_dup(&x, &ray->origin);
	vec3_sub_vec3(&x, &sphere->origin);
	a = vec3_dot_product(&ray->direction, &ray->direction);
	b = 2.0f * vec3_dot_product(&ray->direction, &x);
	c = vec3_dot_product(&x, &x) - sphere->radius2;
	dst = solve_second_quadratic(a, b, c);
	if (0.0f <= dst && (intersect_ret->dst < 0.0f || dst < intersect_ret->dst))
	{
		intersect_ret->dst = dst;
		intersect_ret->nrm = get_point_on_ray(ray, dst);
		vec3_dup(&x, &intersect_ret->nrm);
		vec3_sub_vec3(&x, &sphere->origin);
		vec3_fill(&intersect_ret->nrm, x.x, x.y, x.z);
		vec3_normalize(&intersect_ret->nrm);
		intersect_ret->color = sphere->color;
		set_intensities_res(sphere, intersect_ret);
		intersect_ret->id = sphere->id;
	}
}

static void	set_intensities_res(t_sphere *sphere,
	t_intersect_ret *intersect_ret)
{
	intersect_ret->shininess_intensity = sphere->shininess_intensity;
	intersect_ret->reflexion_intensity = sphere->reflexion_intensity;
	intersect_ret->transparency_intensity = sphere->transparency_intensity;
	intersect_ret->refraction_intensity = sphere->refraction_intensity;
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

static t_color	sphere_map(t_vec3 const *p)
{
	float	theta;
	float	phi;
	float	raw_u;
	float	u;
	float	v;

	theta = atan2f(p->x, p->z);
	phi = acosf(p->y / vec3_get_length(p));
	raw_u = theta / (2.0f * PI);
	u = 1.0f - (raw_u + 0.5f);
	v = 1.0f - (phi / PI);
	return (do_checkboard(16.0f, 8.0f, u, v));
}
