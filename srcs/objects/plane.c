/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:19:02 by aderouba          #+#    #+#             */
/*   Updated: 2023/02/27 10:16:37 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_plane		create_plane(t_vector origin, t_vector normal, int color)
{
	t_plane	res;

	res.origin = origin;
	res.normal = normal;
	res.rev_normal = multiply_vect_number(&normal, -1.0f);
	res.color = color;
	return (res);
}

// param : plane, ray
// result : distance beetween ray origin and plane.
//			if resut < 0, no interection
float	intersect_plane(t_plane *plane, t_ray *ray)
{
	float		denom;
	float		rev_denom;
	float		res;
	t_vector	tmp;

	// Calulation de down part
	denom = dot_product(&ray->direction, &plane->normal);
	rev_denom = dot_product(&ray->direction, &plane->rev_normal);
	// when close to 0 : parallel ton plane
	if (denom > 0.000001f)
	{
		tmp = sub_vect_vect(&plane->origin, &ray->origin);
		res = dot_product(&tmp, &plane->normal);
		res /= denom;
		return (res);
	}
	else if (rev_denom > 0.000001f)
	{
		tmp = sub_vect_vect(&plane->origin, &ray->origin);
		res = dot_product(&tmp, &plane->rev_normal);
		res /= rev_denom;
		return (res);
	}
	return (-1);
}
