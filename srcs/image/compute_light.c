/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:20:07 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/19 13:09:11 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	compute_light(t_all *all, t_intersect_ret *res, t_ray *ray)
{
	t_vec3 const	pixel_pos = get_point_on_ray(ray, res->dst);
	bool			calculate_specular;
	t_light			*light;

	incremente_intensity(res, &all->scene.ambient_light,
		REFLECTION_AMBIANT_RATIO);
	light = all->scene.lights;
	while (light)
	{
		calculate_specular = add_diffuse_intensity(all, res, light,
				&pixel_pos);
		if (calculate_specular)
			add_specular_intensity(all, res, light, &pixel_pos);
		light = light->next;
	}
	apply_transparency(all, res, ray);
	if (res->reflect_limit >= 0)
		mirror_reflection(all, res, ray);
}
