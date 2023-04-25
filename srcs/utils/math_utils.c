/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:02:29 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/25 14:23:55 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

float	solve_quadratic(float a, float b, float c)
{
	float const	discriminant = (b * b) - (4 * a * c);
	float		srqt_discriminant;
	float		denom;
	float		res[2];

	if (discriminant < 0)
		return (-1.0f);
	if (discriminant == 0)
		return ((-b) / (a * 2.0f));
	srqt_discriminant = sqrt(discriminant);
	denom = 1.0f / (a * 2.0f);
	res[0] = (-b - srqt_discriminant) * denom;
	res[1] = (-b + srqt_discriminant) * denom;
	if (res[1] < 0)
		return (res[0]);
	if (0 <= res[0] && res[0] <= res[1])
		return (res[0]);
	return (res[1]);
}

float	solve_second_quadratic(float a, float b, float c)
{
	float const	discriminant = (b * b) - (4 * a * c);
	float		srqt_discriminant;
	float		denom;
	float		res[2];

	if (discriminant < 0)
		return (-1.0f);
	if (discriminant == 0)
		return ((-b) / (a * 2.0f));
	srqt_discriminant = sqrt(discriminant);
	denom = 1.0f / (a * 2.0f);
	res[0] = (-b - srqt_discriminant) * denom;
	res[1] = (-b + srqt_discriminant) * denom;
	if (res[1] < 0)
		return (res[0]);
	if (0 <= res[0] && res[0] >= res[1])
		return (res[0]);
	return (res[1]);
}

t_vec3	get_point_on_ray(t_ray const *ray, float const dist)
{
	t_vec3	point;

	point = ray->origin;
	point.x += ray->direction.x * dist;
	point.y += ray->direction.y * dist;
	point.z += ray->direction.z * dist;
	return (point);
}
