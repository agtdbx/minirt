/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:34:31 by aderouba          #+#    #+#             */
/*   Updated: 2023/02/27 15:56:55 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_vect(t_vector *vector)
{
	printf("vec (%03.3f, %03.3f, %03.3f)\n", vector->x, vector->y, vector->z);
}

void	print_ray(t_ray *ray)
{
	printf("ray (%03.3f, %03.3f, %03.3f) -> (%03.3f, %03.3f, %03.3f)\n",
		ray->origin.x, ray->origin.y, ray->origin.z,
		ray->direction.x, ray->direction.y, ray->direction.z);
}

void	print_sphere(t_sphere *sphere)
{
	printf("sphere (%03.3f, %03.3f, % 03.3f), r = %03.3f\n",
		sphere->origin.x, sphere->origin.y, sphere->origin.z,
		sphere->radius);
}
