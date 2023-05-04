/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:19:02 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/04 19:18:21 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	set_intersecte_ret(t_intersect_ret *intersect_ret, t_plane *plane,
				float dst, t_vec3 *nrm);
static t_color	plane_map(t_vec3 const *p);

t_plane	create_plane(t_vec3 origin, t_vec3 normal, t_color color)
{
	t_plane	res;

	res.origin = origin;
	res.normal = normal;
	vec3_dup(&res.rev_normal, &res.normal);
	vec3_multiply_number(&res.rev_normal, -1.0f);
	res.color = color;
	res.id = -1;
	res.shininess_intensity = 10.0f;
	res.reflexion_intensity = 0.0f;
	res.transparency_intensity = 0.0f;
	res.refraction_intensity = 1.0f;
	return (res);
}

// param : plane, ray
// result : distance beetween ray origin and plane.
//			if resut < 0, no interection
void	intersect_plane(t_plane *plane, t_ray *ray,
			t_intersect_ret *intersect_ret)
{
	float	denom;
	float	dst;
	t_vec3	tmp;

	vec3_dup(&tmp, &plane->origin);
	vec3_sub_vec3(&tmp, &ray->origin);
	denom = vec3_dot_product(&ray->direction, &plane->normal);
	if (denom < 0.000001f)
	{
		dst = vec3_dot_product(&tmp, &plane->normal) / denom;
		if (0.0f <= dst
			&& (intersect_ret->dst < 0.0f || dst < intersect_ret->dst))
			set_intersecte_ret(intersect_ret, plane, dst, &plane->normal);
	}
	else if (denom > -0.000001f)
	{
		dst = vec3_dot_product(&tmp, &plane->rev_normal) / (-denom);
		if (0.0f <= dst
			&& (intersect_ret->dst < 0.0f || dst < intersect_ret->dst))
		{
			set_intersecte_ret(intersect_ret, plane, dst, &plane->rev_normal);

			intersect_ret->color = plane->color;

			// t_vec3	p = get_point_on_ray(ray, dst);
			// vec3_sub_vec3(&p, &plane->origin);
			// intersect_ret->color = plane_map(&p);
		}
	}
}

static void	set_intersecte_ret(t_intersect_ret *intersect_ret, t_plane *plane,
			float dst, t_vec3 *nrm)
{
	intersect_ret->dst = dst;
	vec3_dup(&intersect_ret->nrm, nrm);
	intersect_ret->shininess_intensity = plane->shininess_intensity;
	intersect_ret->reflexion_intensity = plane->reflexion_intensity;
	intersect_ret->transparency_intensity = plane->transparency_intensity;
	intersect_ret->refraction_intensity = plane->refraction_intensity;
	intersect_ret->id = plane->id;
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

static t_color	plane_map(t_vec3 const *p)
{
	float	u;
	float	v;

	u = p->x - (int)p->x;
	v = p->z - (int)p->z;
	return (do_checkboard(16.0f, 8.0f, u, v));
}
