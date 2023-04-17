/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_vec_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:57:16 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/17 16:05:45 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	vec3_add_vec3(t_vec3 *vec, t_vec3 const *vec_to_add)
{
	vec->x += vec_to_add->x;
	vec->y += vec_to_add->y;
	vec->z += vec_to_add->z;
}

void	vec3_sub_vec3(t_vec3 *vec, t_vec3 const *vec_to_sub)
{
	vec->x -= vec_to_sub->x;
	vec->y -= vec_to_sub->y;
	vec->z -= vec_to_sub->z;
}
