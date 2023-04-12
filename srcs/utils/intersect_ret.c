/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_ret.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:03:12 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/12 12:08:12 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_intersect_ret(t_intersect_ret *to_init)
{
	to_init->dst = -1.0f;
	fill_vec(&to_init->nrm, 0.0f, 0.0f, 0.0f);
	to_init->color.r = 0;
	to_init->color.g = 0;
	to_init->color.b = 0;
	to_init->intensity_r = 0.0f;
	to_init->intensity_g = 0.0f;
	to_init->intensity_b = 0.0f;
	to_init->shininess_intensity = 0.0f;
	to_init->reflexion_intensity = 0.0f;
	to_init->id = -1.0f;
}
