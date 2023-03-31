/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:19:02 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/31 12:04:00 by aderouba         ###   ########.fr       */
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
	res.reflexion_intensity = 0.0f;
	return (res);
}

// param : plane, ray
// result : distance beetween ray origin and plane.
//			if resut < 0, no interection
void	intersect_plane(t_plane *plane, t_ray *ray, t_dst_and_nrm *dst_nrm)
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
		if (0.0f <= dst && (dst_nrm->dst < 0.0f || dst < dst_nrm->dst))
		{
			dst_nrm->dst = dst;
			dst_nrm->nrm = plane->normal;
			dst_nrm->color = plane->color;
			dst_nrm->reflexion_intensity = plane->reflexion_intensity;
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
			dst_nrm->reflexion_intensity = plane->reflexion_intensity;
		}
	}
}
