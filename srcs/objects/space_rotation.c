/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:34:36 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/22 12:11:00 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	absolute_rotate(t_vector *vector, float angle, char axis)
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

inline void	my_vect_cpy(t_vector *restrict dst, t_vector const *restrict src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = dst->z;
}

static inline float	loc_dot_prod(float x, float y, float z,
					t_vector const *restrict v)
{
	return ((x * v->x) + (y * v->y) + (z * v->z));
}

/** my_rot_around:
 *   rotate `vect' around normalized `axis' with `angle' (in radians).
 *   -computes rotation matrix using quaternions algebra.
 *   -avoids double coputations using temporary array `t'.
 */
void	my_rot_around(t_vector *restrict vect,
			t_vector const *restrict axis, float angle)
{
	float		t[13];
	t_vector	ret;

	t[0] = cos(angle);
	t[1] = 1.0f - t[0];
	t[2] = axis->x * axis->x;
	t[3] = t[1] * axis->x;
	t[4] = t[3] * axis->y;
	t[5] = sin(angle);
	t[6] = t[5] * axis->z;
	t[7] = t[3] * axis->z;
	t[8] = t[5] * axis->y;
	t[9] = axis->y * axis->y;
	t[10] = t[1] * axis->y * axis->z;
	t[11] = t[5] * axis->x;
	t[12] = axis->z * axis->z;
	ret.x = loc_dot_prod(t[0] + t[1] * t[2], t[4] - t[6], t[7] + t[8], vect);
	ret.y = loc_dot_prod(t[4] + t[6], t[0] + t[1] * t[9], t[10] - t[11], vect);
	ret.z = loc_dot_prod(t[7] - t[8], t[10] + t[11], t[0] + t[1] * t[12], vect);
	my_vect_cpy(vect, &ret);
}
