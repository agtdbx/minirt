/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:20:07 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/02 09:58:42 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	compute_light(t_all *all, t_intersect_ret *res, t_ray *ray)
{
	int				i;
	t_vec3 const	pixel_pos = get_point_on_ray(ray, res->dst);
	bool			calculate_specular;

	incremente_intensity(res, &all->scene.ambient_light,
		REFLECTION_AMBIANT_RATIO);
	i = 0;
	while (i < 1)
	{
		calculate_specular = add_diffuse_intensity(all, res, &all->scene.light,
				&pixel_pos);
		if (calculate_specular)
			add_specular_intensity(all, res, &all->scene.light, &pixel_pos);
		i++;
	}
	apply_transparency(all, res, ray);
	if (res->reflect_limit >= 0)
		mirror_reflection(all, res, ray);
}
