/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparency.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:38:10 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/25 19:23:48 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	sphere_transparency(t_all *all, t_intersect_ret *res, t_ray *ray,
				t_sphere *sphere);
static void	plane_transparency(t_all *all, t_intersect_ret *res, t_ray *ray);
static void	cylinder_transparency(t_all *all, t_intersect_ret *res, t_ray *ray,
				t_cylinder *cylinder);
static t_vec3	refract(t_vec3 *ray, t_vec3 *normal, float in, float out);

void	apply_transparency(t_all *all, t_intersect_ret *res, t_ray *ray)
{
	t_rtlst	*obj;

	if (res->transparency_intensity == 0.0f)
		return ;
	obj = all->scene.objects;
	while (obj)
	{
		if (obj->id == res->id)
		{
			if (obj->type == SPHERE)
				sphere_transparency(all, res, ray, &obj->value.as_sphere);
			else if (obj->type == PLANE)
				plane_transparency(all, res, ray);
			else if (obj->type == CYLINDER)
				cylinder_transparency(all, res, ray, &obj->value.as_cylinder);
		}
		obj = obj->next;
	}
}

static void	sphere_transparency(t_all *all, t_intersect_ret *res, t_ray *ray,
				t_sphere *sphere)
{
	t_vec3			point;
	t_intersect_ret	transparency_res;
	t_ray			transparency_ray;

	transparency_ray.origin = get_point_on_ray(ray, res->dst);
	transparency_ray.direction = refract(&ray->direction,
		&res->nrm, 1.0f, res->refraction_intensity);

	init_intersect_ret(&transparency_res);
	intersect_second_sphere(sphere, &transparency_ray, &transparency_res);
	if (transparency_res.dst < 0.0f)
		return ;

	point = get_point_on_ray(&transparency_ray, transparency_res.dst);
	vec3_dup(&transparency_ray.origin, &point);
	transparency_ray.direction = refract(&transparency_ray.direction,
		&transparency_res.nrm, transparency_res.refraction_intensity, 1.0f);

	init_intersect_ret(&transparency_res);
	do_intersections_without_id(all, &transparency_res, &transparency_ray,
		res->id);

	compute_light(all, &transparency_res, ray, MAX_REFLECT);
	merge_pixels(res, &transparency_res, res->transparency_intensity);
}

static void	plane_transparency(t_all *all, t_intersect_ret *res, t_ray *ray)
{
	t_intersect_ret	transparency_res;

	init_intersect_ret(&transparency_res);
	do_intersections_without_id(all, &transparency_res, ray,
		res->id);
	compute_light(all, &transparency_res, ray, MAX_REFLECT);
	merge_pixels(res, &transparency_res, res->transparency_intensity);
}

static void	cylinder_transparency(t_all *all, t_intersect_ret *res, t_ray *ray,
				t_cylinder *cylinder)
{
	(void)all;
	(void)res;
	(void)ray;
	(void)cylinder;
}

static t_vec3	refract(t_vec3 *ray, t_vec3 *normal, float in, float out)
{
	float const	c = vec3_dot_product(ray, normal);
	float const	r = in / out;
	t_vec3		res;
	t_vec3		tmp;

	vec3_dup(&res, ray);
	vec3_multiply_number(&res, -r);
	vec3_dup(&tmp, normal);
	vec3_multiply_number(&tmp, r*c - sqrtf(1 - powf(r, 2) * (1 - powf(c, 2))));
	vec3_add_vec3(&res, &tmp);
	return (res);
}
