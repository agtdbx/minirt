/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:19:02 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/22 13:46:27 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_plane	create_plane(t_vector origin, t_vector normal, int color)
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
void	intersect_plane(t_plane *plane, t_ray *ray, t_dst_and_nrm *dst_nrm)
{
	float			denom;
	float			dst;
	const t_vector	tmp = sub_vect_vect(&plane->origin, &ray->origin);

	denom = dot_product(&ray->direction, &plane->normal);
	if (denom < 0.000001f)
	{
		dst = dot_product(&tmp, &plane->normal) / denom;
		if (0.0f <= dst && (dst_nrm->dst < 0.0f || dst < dst_nrm->dst))
		{
			dst_nrm->dst = dst;
			dst_nrm->nrm = plane->normal;
			dst_nrm->color = plane->color;
		}
	}
	else if (denom > -0.000001f)
	{
		dst = dot_product(&tmp, &plane->rev_normal) / (-denom);
		if (0.0f <= dst && (dst_nrm->dst < 0.0f || dst < dst_nrm->dst))
		{
			dst_nrm->dst = dst;
			dst_nrm->nrm = plane->rev_normal;
			dst_nrm->color = plane->color;
		}
	}
}
