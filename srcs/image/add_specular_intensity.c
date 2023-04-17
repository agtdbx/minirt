/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_specular_intensity.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:23:20 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/17 16:18:02 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	add_specular_intensity(t_all *all, t_intersect_ret *res,
			t_light const *light, t_vec3 const *pixel_pos)
{
	t_vec3	reflection_direction;
	t_vec3	direction_from_light;
	t_vec3	tmp;
	float	angle_ratio;
	float	intensity;

	if (res->shininess_intensity == 0.0f)
		return ;
	vec3_dup(&direction_from_light, pixel_pos);
	vec3_sub_vec3(&direction_from_light, &light->pos);
	vec3_dup(&tmp, &res->nrm);
	vec3_multiply_number(&tmp,
		2 * vec3_dot_product(&direction_from_light, &res->nrm));
	vec3_dup(&reflection_direction, &tmp);
	vec3_sub_vec3(&reflection_direction, &direction_from_light);
	vec3_dup(&tmp, pixel_pos);
	vec3_sub_vec3(&tmp, &all->scene.camera.pos);
	vec3_normalize(&tmp);
	vec3_normalize(&reflection_direction);
	angle_ratio = vec3_dot_product(&tmp, &reflection_direction);
	if (angle_ratio <= 0.0f)
		return ;
	angle_ratio = powf(angle_ratio, res->shininess_intensity);
	intensity = angle_ratio * REFLECTION_SPECULAR_RATIO;
	incremente_intensity(res, light, intensity);
}
