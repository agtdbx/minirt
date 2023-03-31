/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:47:41 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/31 12:04:04 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_sphere	create_sphere(t_vector origin, float diameter, t_color color)
{
	t_sphere	res;

	res.origin = origin;
	res.radius = diameter / 2.0f;
	res.radius2 = res.radius * res.radius;
	res.color = color;
	res.reflexion_intensity = 0.0f;
	return (res);
}

// param : sphere, ray
// result : distance beetween ray origin and sphere.
//			if resut < 0, no interection
void	intersect_sphere(t_sphere *sphere, t_ray *ray,
			t_dst_and_nrm *dst_nrm)
{
	float		dst;
	float		a;
	float		b;
	float		c;
	t_vector	x;

	dup_vec(&x, &ray->origin);
	sub_vec_vec(&x, &sphere->origin);
	a = dot_product(&ray->direction, &ray->direction);
	b = 2.0f * dot_product(&ray->direction, &x);
	c = dot_product(&x, &x) - sphere->radius2;
	dst = solve_quadratic(a, b, c);
	if (0.0f <= dst && (dst_nrm->dst < 0.0f || dst < dst_nrm->dst))
	{
		dst_nrm->dst = dst;
		dst_nrm->nrm = get_point_on_ray(ray, dst);
		dup_vec(&x, &dst_nrm->nrm);
		sub_vec_vec(&x, &sphere->origin);
		fill_vec(&dst_nrm->nrm, x.x, x.y, x.z);
		normalize_vec(&dst_nrm->nrm);
		dst_nrm->color = sphere->color;
		dst_nrm->reflexion_intensity = sphere->reflexion_intensity;
	}
}
