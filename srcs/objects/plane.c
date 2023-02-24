/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:19:02 by aderouba          #+#    #+#             */
/*   Updated: 2023/02/24 18:37:22 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// param : plane, ray
// result : distance beetween ray origin and plane.
//			if resut < 0, no interection
float	intersect_plane(t_plane *plane, t_ray *ray)
{
	float		denom;
	float		res;
	t_vector	tmp;

	denom = dot_product(&ray->direction, &plane->direction);
	if (denom > 0.000001f)
	{
		tmp = sub_vect_vect(&plane->origin, &ray->origin);
		res = dot_product(&tmp, &plane->direction);
		res /= denom;
		return (res);
	}
	return (-1);
}
