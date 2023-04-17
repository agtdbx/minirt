/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:59:53 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/17 16:05:45 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

float	vec3_get_length(t_vec3 *vec)
{
	return (sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z)));
}

void	vec3_normalize(t_vec3 *vec)
{
	const float	x = vec->x;
	const float	y = vec->y;
	const float	z = vec->z;
	float		length;

	if (x != 0.0f || y != 0.0f || z != 0.0f)
	{
		length = vec3_get_length(vec);
		vec->x /= length;
		vec->y /= length;
		vec->z /= length;
	}
}

float	vec3_dot_product(t_vec3 const *v1, t_vec3 const *v2)
{
	return ((v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z));
}

void	vec3_cross_product(t_vec3 const *v1, t_vec3 const *v2, t_vec3 *vec_res)
{
	vec_res->x = (v1->y * v2->z) - (v1->z * v2->y);
	vec_res->y = (v1->z * v2->x) - (v1->x * v2->z);
	vec_res->z = (v1->x * v2->y) - (v1->y * v2->x);
}
