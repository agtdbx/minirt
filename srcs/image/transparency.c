/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparency.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:38:10 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/26 13:11:58 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	sphere_transparency(t_all *all, t_intersect_ret *res, t_ray *ray,
				t_sphere *sphere);
static void	plane_transparency(t_all *all, t_intersect_ret *res, t_ray *ray);
static void	cylinder_transparency(t_all *all, t_intersect_ret *res, t_ray *ray,
				t_cylinder *cylinder);
static bool	refract(t_vec3 const *v, t_vec3 const *n, float ni_over_nt,
				t_vec3 *refracted);
static void	transparency_reflect(t_all *all, t_intersect_ret *res, t_ray *ray);

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
	init_intersect_ret(&refraction_res);
	intersect_second_sphere(sphere, &refraction_ray, &refraction_res);
	if (refraction_res.dst < 0.0f)
		return ;
	transparency_ray.origin = get_point_on_ray(&refraction_ray,
			refraction_res.dst);
	ni_over_nt = res->refraction_intensity / 1.0f;
	vec3_multiply_number(&refraction_res.nrm, -1.0f);
	if (refract(&refraction_ray.direction, &refraction_res.nrm, ni_over_nt,
			&transparency_ray.direction) == false)
		return ;
	init_intersect_ret(&transparency_res);
	do_intersections_without_id(all, &transparency_res, &transparency_ray,
		res->id);
	compute_light(all, &transparency_res, &transparency_ray, MAX_REFLECT);
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
	init_intersect_ret(&refraction_res);
	intersect_second_cylinder(cylinder, &refraction_ray, &refraction_res);
	if (refraction_res.dst < 0.0f)
		return ;
	transparency_ray.origin = get_point_on_ray(&refraction_ray,
			refraction_res.dst);
	ni_over_nt = res->refraction_intensity / 1.0f;
	vec3_multiply_number(&refraction_res.nrm, -1.0f);
	if (refract(&refraction_ray.direction, &refraction_res.nrm, ni_over_nt,
			&transparency_ray.direction) == false)
		return ;
	init_intersect_ret(&transparency_res);
	do_intersections_without_id(all, &transparency_res, &transparency_ray,
		res->id);
	compute_light(all, &transparency_res, &transparency_ray, MAX_REFLECT);
	merge_pixels(res, &transparency_res, res->transparency_intensity);
}

static bool	refract(t_vec3 const *v, t_vec3 const *n, float ni_over_nt,
				t_vec3 *refracted)
{
	t_vec3	uv;
	float	dt;
	float	discriminat;
	t_vec3	tmp;

	vec3_dup(&uv, v);
	vec3_normalize(&uv);
	dt = vec3_dot_product(&uv, n);
	discriminat = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);
	if (discriminat > 0.0f)
	{
		vec3_dup(refracted, &uv);
		vec3_dup(&tmp, n);
		vec3_multiply_number(&tmp, dt);
		vec3_sub_vec3(refracted, &tmp);
		vec3_multiply_number(refracted, ni_over_nt);
		vec3_dup(&tmp, n);
		vec3_multiply_number(&tmp, sqrt(discriminat));
		vec3_sub_vec3(refracted, &tmp);
		return (true);
	}
	return (false);
}

static void	transparency_reflect(t_all *all, t_intersect_ret *res, t_ray *ray)
{
	t_vec3			tmp;
	t_intersect_ret	transparency_res;
	t_ray			transparency_ray;

	vec3_dup(&tmp, &res->nrm);
	vec3_multiply_number(&tmp,
		2 * vec3_dot_product(&ray->direction, &res->nrm));
	transparency_ray.origin = get_point_on_ray(ray, res->dst);
	vec3_dup(&transparency_ray.direction, &ray->direction);
	vec3_sub_vec3(&transparency_ray.direction, &tmp);
	init_intersect_ret(&transparency_res);
	do_intersections_without_id(all, &transparency_res, &transparency_ray,
		res->id);
	compute_light(all, &transparency_res, &transparency_ray, MAX_REFLECT);
	merge_pixels(res, &transparency_res, res->transparency_intensity);
}
