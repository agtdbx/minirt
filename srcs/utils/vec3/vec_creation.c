/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:53:12 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/17 16:37:46 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	vec3_fill(t_vec3 *vec, float const x, float const y, float const z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

void	vec3_dup(t_vec3 *vec, t_vec3 const *vec_to_dup)
{
	vec->x = vec_to_dup->x;
	vec->y = vec_to_dup->y;
	vec->z = vec_to_dup->z;
}
