/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:34:36 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/15 11:50:55 by aderouba         ###   ########.fr       */
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
	const float	z = vector->x;

	if (axis == ROTATE_AROUND_X)
	{
		vector->y = cos(angle * PI_DIV_180) * y + sin(angle * PI_DIV_180) * z;
		vector->z = -sin(angle * PI_DIV_180) * y + cos(angle * PI_DIV_180) * z;
	}
	else if (axis == ROTATE_AROUND_Y)
	{
		vector->x = cos(angle * PI_DIV_180) * x + sin(angle * PI_DIV_180) * z;
		vector->z = -sin(angle * PI_DIV_180) * x + cos(angle * PI_DIV_180) * z;
	}
	else if (axis == ROTATE_AROUND_Z)
	{
		vector->x = cos(angle * PI_DIV_180) * x + sin(angle * PI_DIV_180) * y;
		vector->y = -sin(angle * PI_DIV_180) * x + cos(angle * PI_DIV_180) * y;
	}
}
