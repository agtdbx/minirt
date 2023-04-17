/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_get_normals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:28:30 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/17 16:05:45 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	vec3_get_normals(t_vec3 const *vect, t_vec3 nrm[2])
{
	nrm[0].x = 1.0f;
	nrm[0].y = (-vect->x) / vect->y;
	nrm[0].z = 0.0f;
	vec3_cross_product(vect, &nrm[0], &nrm[1]);
}
