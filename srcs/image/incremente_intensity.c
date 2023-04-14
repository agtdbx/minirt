/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incremente_intensity.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:30:31 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/14 11:52:28 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	incremente_intensity(t_intersect_ret *res, t_light const *light,
			float const reflection_ratio)
{
	res->intensity_r += light->intensity_r * light->brightness
		* reflection_ratio;
	res->intensity_g += light->intensity_g * light->brightness
		* reflection_ratio;
	res->intensity_b += light->intensity_b * light->brightness
		* reflection_ratio;
}
