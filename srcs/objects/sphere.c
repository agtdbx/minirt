/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:47:41 by aderouba          #+#    #+#             */
/*   Updated: 2023/02/27 10:13:25 by aderouba         ###   ########.fr       */
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
// float	intersect_sphere(t_sphere *sphere, t_ray *ray)
// {
// 	float		res;
// 	float		res2;
// 	t_vector	abc;
// 	t_vector	x;
// 	float		discriminant;

// 	x = sub_vect_vect(&ray->origin, &sphere->origin);
// 	abc.x = dot_product(&ray->direction, &ray->direction);
// 	abc.y = 2.0f * dot_product(&ray->direction, &x);
// 	abc.z = dot_product(&x, &x)
// 		- sphere->radius2;
// 	discriminant = calculate_discriminant(abc.x, abc.y, abc.z);
// 	if (discriminant == 0.0f)
// 		res = equation_result(abc.x, abc.y);
// 	else if (discriminant > 0.0f)
// 	{
// 		res = equation_minus_result(abc.x, abc.y, discriminant);
// 		res2 = equation_plus_result(abc.x, abc.y, discriminant);
// 		if (res2 >= 0.0f && res2 < res)
// 			res = res2;
// 	}
// 	else
// 		res = -1.0f;
// 	return (res);
// }
float	intersect_sphere(t_sphere *sphere, t_ray *ray)
{
	float		res[2];
	float		a;
	float		b;
	float		c;
	float		discriminant;
	t_vector	x;

	// Calcule for optimisation
	x = sub_vect_vect(&ray->origin, &sphere->origin);

	// Calcule a b c for second degrees equation
	a = dot_product(&ray->direction, &ray->direction);
	b = 2.0f * dot_product(&ray->direction, &x);
	c = dot_product(&x, &x)
		- sphere->radius2;

	// Calcule discriminant
	discriminant = calculate_discriminant(a, b, c);
	if (discriminant == 0.0f) // if equals 0, one result
		res[0] = equation_result(a, b);
	else if (discriminant > 0.0f) // if more than 0, deux results
	{
		// Calculate results
		res[0] = 0.0f;
		res[1] = 0.0f;
		equation_both_result(a, b, discriminant, res);
		// chose the closest result
		if (res[1] >= 0.0f && (res[1] < res[0] || res[0] == -1.0f))
			res[0] = res[1];
	}
	else // if less than 0, no result
		res[0] = -1.0f;

	return (res[0]);
}
