/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:34:36 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/20 08:55:53 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	translate(t_vector *vector, float x, float y, float z)
{
	vector->x += x;
	vector->y += y;
	vector->z += z;
}

void	rotate(t_vector *vector, float angle, char axis)
{
	const float	x = vector->x;
	const float	y = vector->y;
	const float	z = vector->z;
	const float	rad = angle * PI_DIV_180;

	if (axis == ROTATE_AROUND_X)
	{
		vector->y = cos(rad) * y + sin(rad) * z;
		vector->z = -sin(rad) * y + cos(rad) * z;
	}
	else if (axis == ROTATE_AROUND_Y)
	{
		vector->x = cos(rad) * x + sin(rad) * z;
		vector->z = -sin(rad) * x + cos(rad) * z;
	}
	else if (axis == ROTATE_AROUND_Z)
	{
		vector->x = cos(rad) * x + sin(rad) * y;
		vector->y = -sin(rad) * x + cos(rad) * y;
	}
}
