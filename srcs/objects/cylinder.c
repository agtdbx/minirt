/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:29:55 by aderouba          #+#    #+#             */
/*   Updated: 2023/02/27 10:30:36 by aderouba         ###   ########.fr       */
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

	// res.bot_origin = origin;
	// res.bot_origin.x += rev_axis.x * (height / 2.0f);
	// res.bot_origin.y += rev_axis.y * (height / 2.0f);
	// res.bot_origin.z += rev_axis.z * (height / 2.0f);

	// res.top_origin = origin;
	// res.top_origin.x += axis.x * (height / 2.0f);
	// res.top_origin.y += axis.y * (height / 2.0f);
	// res.top_origin.z += axis.z * (height / 2.0f);

	// res.bot = create_plane(res.bot.origin, rev_axis, 0XFFFFFFFF);
	// res.top = create_plane(res.top.origin, axis, 0XFFFFFFFF);

	res.axis = axis;
	res.radius = diameter / 2.0f;
	res.radius2 = res.radius * res.radius;
	res.height = height;
	res.half_height = height / 2.0f;
	res.neg_half_height = res.half_height * -1.0f;
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
	float		res[2];
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
	c = dot_product(&x, &x) - xv - cylinder->radius2;

	// Calcule discriminant
	discriminant = calculate_discriminant(a, b, c);
	if (discriminant == 0.0f) // if equals 0, one result
	{
		res[0] = equation_result(a, b);
		m = dv * res[0] + xv;
	}
	else if (discriminant >= 0.0f) // if more than 0, deux results
	{
		// Calculate results
		res[0] = 0.0f;
		res[1] = 0.0f;
		equation_both_result(a, b, discriminant, res);

		// Calculate the distance from the origin of the cylinder
		m = dv * res[0] + xv;
		m2 = dv * res[0] + xv;

		if (res[1] >= 0.0f &&  (res[1] < res[0] || res[0] == -1.0f)
			&& m2 >= cylinder->neg_half_height
			&& m2 <= cylinder->half_height) // chose the closest result in cylinder
		{
			res[0] = res[1];
			m = m2;
		}
	}
	else // if less than 0, no result
	{
		res[0] = -1.0f;
		m = 0.0f;
	}
	// if the distance from the origin of the cylinder
	// is negatif or more than height, the point isn't in the cylinder
	if (m < cylinder->neg_half_height || m > cylinder->half_height)
		res[0] = -1.0f;

	return (res[0]);
}
