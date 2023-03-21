/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:47:41 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/21 10:45:46 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_sphere	create_sphere(t_vector origin, float radius, int color)
{
	t_sphere	res;

	res.origin = origin;
	res.radius = radius;
	res.radius2 = radius * radius;
	res.color = color;
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

	x = sub_vect_vect(&ray->origin, &sphere->origin);
	a = dot_product(&ray->direction, &ray->direction);
	b = 2.0f * dot_product(&ray->direction, &x);
	c = dot_product(&x, &x) - sphere->radius2;
	dst = solve_quadratic(a, b, c);
	if (0.0f <= dst && (dst_nrm->dst < 0.0f || dst < dst_nrm->dst))
	{
		dst_nrm->dst = dst;
		dst_nrm->nrm = get_point_on_ray(ray, dst);
		x = sub_vect_vect(&dst_nrm->nrm, &sphere->origin);
		dst_nrm->nrm = create_vector(x.x, x.y, x.z, true);
		dst_nrm->color = sphere->color;
	}
}
