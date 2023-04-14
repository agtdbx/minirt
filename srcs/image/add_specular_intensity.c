/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_specular_intensity.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:23:20 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/14 11:51:04 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	add_specular_intensity(t_all *all, t_intersect_ret *res,
			t_light const *light, t_vector const *pixel_pos)
{
	t_vector	reflection_direction;
	t_vector	direction_from_light;
	t_vector	tmp;
	float		angle_ratio;
	float		intensity;

	if (res->shininess_intensity == 0.0f)
		return ;
	dup_vec(&direction_from_light, pixel_pos);
	sub_vec_vec(&direction_from_light, &light->pos);
	dup_vec(&tmp, &res->nrm);
	multiply_vec_number(&tmp,
		2 * dot_product(&direction_from_light, &res->nrm));
	dup_vec(&reflection_direction, &tmp);
	sub_vec_vec(&reflection_direction, &direction_from_light);
	dup_vec(&tmp, pixel_pos);
	sub_vec_vec(&tmp, &all->scene.camera.pos);
	normalize_vec(&tmp);
	normalize_vec(&reflection_direction);
	angle_ratio = dot_product(&tmp, &reflection_direction);
	if (angle_ratio <= 0.0f)
		return ;
	angle_ratio = powf(angle_ratio, res->shininess_intensity);
	intensity = angle_ratio * REFLECTION_SPECULAR_RATIO;
	incremente_intensity(res, light, intensity);
}
