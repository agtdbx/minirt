/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:47:41 by aderouba          #+#    #+#             */
/*   Updated: 2023/02/24 17:18:36 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_sphere	create_sphere(t_vector origin, int radius, int color)
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
float	intersect_sphere(t_sphere *sphere, t_ray *ray)
{
	float		res;
	float		res2;
	t_vector	abc;
	t_vector	origin_minus_center;
	float		discriminant;

	origin_minus_center = sub_vect_vect(&ray->origin, &sphere->origin);
	abc.x = dot_product(&ray->direction, &ray->direction);
	abc.y = 2.0f * dot_product(&ray->direction, &origin_minus_center);
	abc.z = dot_product(&origin_minus_center, &origin_minus_center)
		- sphere->radius2;
	discriminant = calculate_discriminant(abc.x, abc.y, abc.z);
	if (discriminant == 0.0f)
		res = equation_result(abc.x, abc.y);
	else if (discriminant > 0.0f)
	{
		res = equation_minus_result(abc.x, abc.y, discriminant);
		res2 = equation_plus_result(abc.x, abc.y, discriminant);
		if (res2 >= 0.0f && res2 < res)
			res = res2;
	}
	else
		res = -1.0f;
	return (res);
}
