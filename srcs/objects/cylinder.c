/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:29:55 by aderouba          #+#    #+#             */
/*   Updated: 2023/02/25 16:39:01 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_cylinder	create_cylinder(t_vector origin, t_vector axis, float diameter,
				float height)
{
	t_cylinder	res;
	t_vector	rev_axis;

	rev_axis = multiply_vect_number(&axis, -1.0f);
	res.origin = origin;

	res.bot_origin = origin;
	res.bot_origin.x += rev_axis.x * (height / 2.0f);
	res.bot_origin.y += rev_axis.y * (height / 2.0f);
	res.bot_origin.z += rev_axis.z * (height / 2.0f);

	res.top_origin = origin;
	res.top_origin.x += axis.x * (height / 2.0f);
	res.top_origin.y += axis.y * (height / 2.0f);
	res.top_origin.z += axis.z * (height / 2.0f);

	res.bot = create_plane(res.bot.origin, rev_axis, 0XFFFFFFFF);
	res.top = create_plane(res.top.origin, axis, 0XFFFFFFFF);

	res.axis = axis;
	res.diameter = diameter;
	res.diameter2 = diameter * diameter;
	res.height = height;
	res.color = 0;
	return (res);
}

void		set_cylinder_color(t_cylinder *cylinder, int color)
{
	cylinder->color = color;
	cylinder->bot.color = color;
	cylinder->top.color = color;
}

// param : cylinder, ray
// result : distance beetween ray origin and cylinder.
//			if resut < 0, no interection
float	intersect_cylinder(t_cylinder *cylinder, t_ray *ray)
{
	float		res;
	float		res2;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	float		m;
	float		m2;
	t_vector	x;
	float		dv;
	float		xv;

	// Calcule for optimisation
	x = sub_vect_vect(&ray->origin, &cylinder->origin);
	dv = dot_product(&ray->direction, &cylinder->axis);
	xv = dot_product(&x, &cylinder->axis);

	// Calcule a b c for second degrees equation
	a = dot_product(&ray->direction, &ray->direction) - dv;
	b = (dot_product(&ray->direction, &x) - dv * xv) * 2.0f;
	c = dot_product(&x, &x) - xv - cylinder->diameter2;

	// Calcule discriminant
	discriminant = calculate_discriminant(a, b, c);
	if (discriminant >= 0 && b == 0.0f) // In this case, res will be nan
	{
		res = intersect_plane(&cylinder->bot, ray);
		res2 = intersect_plane(&cylinder->top, ray);

		if (res2 >= 0.0f &&  (res2 < res || res == -1.0f))
			res = res2;
		m = 0.0f;
	}
	else if (discriminant == 0.0f) // if equals 0, one result
	{
		res = equation_result(a, b);
		m = dv * res + xv;
	}
	else if (discriminant > 0.0f) // if more than 0, deux results
	{
		// Calculate results
		res = equation_minus_result(a, b, discriminant);
		res2 = equation_plus_result(a, b, discriminant);

		// Calculate the distance from the origin of the cylinder
		m = dv * res + xv;
		m2 = dv * res + xv;

		if (res2 >= 0.0f &&  (res2 < res || res == -1.0f) && m2 >= 0
			&& m2 <= cylinder->height) // chose the closest result in cylinder
		{
			res = res2;
			m = m2;
		}
	}
	else // if less than 0, no result
	{
		res = -1.0f;
		m = 0.0f;
	}
	// if the distance from the origin of the cylinder
	// is negatif or more than height, the point isn't in the cylinder
	if (m < 0 || m > cylinder->height)
		res = -1.0f;

	return (res);
}
