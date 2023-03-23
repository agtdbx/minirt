/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:28:30 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/23 13:11:00 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	fill_vec(t_vector *vec, float const x, float const y, float const z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

void	dup_vec(t_vector *vec, t_vector const *vec_to_dup)
{
	vec->x = vec_to_dup->x;
	vec->y = vec_to_dup->y;
	vec->z = vec_to_dup->z;
}

float	get_length_vec(t_vector *vec)
{
	return (sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z)));
}

void	normalize_vec(t_vector *vec)
{
	const float	x = vec->x;
	const float	y = vec->y;
	const float	z = vec->z;
	float		length;

	if (x != 0.0f || y != 0.0f || z != 0.0f)
	{
		length = get_length_vec(vec);
		vec->x /= length;
		vec->y /= length;
		vec->z /= length;
	}
}

void	multiply_vec_number(t_vector *vec, float const number)
{
	vec->x *= number;
	vec->y *= number;
	vec->z *= number;
}

void	add_vec_vec(t_vector *vec, t_vector const *vec_to_add)
{
	vec->x += vec_to_add->x;
	vec->y += vec_to_add->y;
	vec->z += vec_to_add->z;
}

void	sub_vec_vec(t_vector *vec, t_vector const *vec_to_sub)
{
	vec->x -= vec_to_sub->x;
	vec->y -= vec_to_sub->y;
	vec->z -= vec_to_sub->z;
}

float	dot_product(t_vector const *v1, t_vector const *v2)
{
	return ((v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z));
}

void	cross_product(t_vector const *v1, t_vector const *v2, t_vector *vec_res)
{
	vec_res->x = (v1->y * v2->z) - (v1->z * v2->y);
	vec_res->y = (v1->z * v2->x) - (v1->x * v2->z);
	vec_res->z = (v1->x * v2->y) - (v1->y * v2->x);
}

void	get_normals_of_vect(t_vector const *vect, t_vector nrm[2])
{
	nrm[0].x = 1.0f;
	nrm[0].y = (-vect->x) / vect->y;
	nrm[0].z = 0.0f;
	cross_product(vect, &nrm[0], &nrm[1]);
}
