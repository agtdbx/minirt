/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:28:30 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/17 13:01:50 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_vector	create_vector(float x, float y, float z, bool normalize)
{
	t_vector	res;
	float		length;

	res.x = x;
	res.y = y;
	res.z = z;
	if (normalize && (x != 0.0f || y != 0.0f || z != 0.0f))
	{
		length = sqrt((x * x) + (y * y) + (z * z));
		res.x /= length;
		res.y /= length;
		res.z /= length;
	}
	return (res);
}

t_vector	multiply_vect_number(t_vector const *vector, float const number)
{
	t_vector	res;

	res.x = vector->x * number;
	res.y = vector->y * number;
	res.z = vector->z * number;
	return (res);
}

t_vector	add_vect_vect(t_vector const *v1, t_vector const *v2)
{
	t_vector	res;

	res.x = v1->x + v2->x;
	res.y = v1->y + v2->y;
	res.z = v1->z + v2->z;
	return (res);
}

t_vector	sub_vect_vect(t_vector const *v1, t_vector const *v2)
{
	t_vector	res;

	res.x = v1->x - v2->x;
	res.y = v1->y - v2->y;
	res.z = v1->z - v2->z;
	return (res);
}

float	dot_product(t_vector const *v1, t_vector const *v2)
{
	return ((v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z));
}

t_vector	cross_product(t_vector const *v1, t_vector const *v2)
{
	t_vector	res;

	res.x = (v1->y * v2->z) - (v1->z * v2->y);
	res.y = (v1->z * v2->x) - (v1->x * v2->z);
	res.z = (v1->x * v2->y) - (v1->y * v2->x);
	return (res);
}

void	get_normals_of_vect(t_vector const *vect, t_vector nrm[2])
{
	nrm[0].x = 1.0f;
	nrm[0].y = (-vect->x) / vect->y;
	nrm[0].z = 0.0f;
	nrm[1] = cross_product(vect, &nrm[0]);
}
