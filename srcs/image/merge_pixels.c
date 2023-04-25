/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_pixels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:56:12 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/25 17:57:17 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	merge_pixels(t_intersect_ret *res,
			t_intersect_ret *transparency_res, float intensity)
{
	float const	inv_intensity = (1.0f - intensity);

	res->color.r = (float)res->color.r * inv_intensity
		+ (float)transparency_res->color.r * intensity;
	res->color.g = (float)res->color.g * inv_intensity
		+ (float)transparency_res->color.g * intensity;
	res->color.b = (float)res->color.b * inv_intensity
		+ (float)transparency_res->color.b * intensity;
	res->intensity_r = res->intensity_r * inv_intensity
		+ transparency_res->intensity_r * intensity;
	res->intensity_g = res->intensity_g * inv_intensity
		+ transparency_res->intensity_g * intensity;
	res->intensity_b = res->intensity_b * inv_intensity
		+ transparency_res->intensity_b * intensity;
}
