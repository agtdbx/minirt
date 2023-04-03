/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:19:02 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/03 10:18:05 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_plane	create_plane(t_vector origin, t_vector normal, t_color color)
{
	t_plane	res;

	res.origin = origin;
	res.normal = normal;
	dup_vec(&res.rev_normal, &res.normal);
	multiply_vec_number(&res.rev_normal, -1.0f);
	res.color = color;
	res.id = -1;
	res.reflexion_intensity = 0.2f;
	return (res);
}

// param : plane, ray
// result : distance beetween ray origin and plane.
//			if resut < 0, no interection
void	intersect_plane(t_plane *plane, t_ray *ray, t_intersect_ret *intersect_ret)
{
	float		denom;
	float		dst;
	t_vector 	tmp;

	dup_vec(&tmp, &plane->origin);
	sub_vec_vec(&tmp, &ray->origin);
	denom = dot_product(&ray->direction, &plane->normal);
	if (denom < 0.000001f)
	{
		dst = dot_product(&tmp, &plane->normal) / denom;
		if (0.0f <= dst && (intersect_ret->dst < 0.0f || dst < intersect_ret->dst))
		{
			intersect_ret->dst = dst;
			intersect_ret->nrm = plane->normal;
			intersect_ret->color = plane->color;
			intersect_ret->reflexion_intensity = plane->reflexion_intensity;
			intersect_ret->id = plane->id;
		}
	}
	else if (denom > -0.000001f)
	{
		dst = dot_product(&tmp, &plane->rev_normal) / (-denom);
		if (0.0f <= dst && (intersect_ret->dst < 0.0f || dst < intersect_ret->dst))
		{
			intersect_ret->dst = dst;
			intersect_ret->nrm = plane->rev_normal;
			intersect_ret->color = plane->color;
			intersect_ret->reflexion_intensity = plane->reflexion_intensity;
			intersect_ret->id = plane->id;
		}
	}
}
