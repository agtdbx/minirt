/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:34:31 by aderouba          #+#    #+#             */
/*   Updated: 2023/02/24 16:25:12 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_vect(t_vector *vector)
{
	printf("vec (%.3f, %.3f, %.3f)\n", vector->x, vector->y, vector->z);
}

void	print_ray(t_ray *ray)
{
	printf("ray (%.3f, %.3f, %.3f) -> (%.3f, %.3f, %.3f)\n",
		ray->origin.x, ray->origin.y, ray->origin.z,
		ray->direction.x, ray->direction.y, ray->direction.z);
}

void	print_sphere(t_sphere *sphere)
{
	printf("sphere (%.3f, %.3f, %.3f), r = %f\n",
		sphere->origin.x, sphere->origin.y, sphere->origin.z,
		sphere->radius);
}
