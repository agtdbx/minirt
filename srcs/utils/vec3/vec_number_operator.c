/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_number_operator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:58:27 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/17 16:05:45 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	vec3_multiply_number(t_vec3 *vec, float const number)
{
	vec->x *= number;
	vec->y *= number;
	vec->z *= number;
}
