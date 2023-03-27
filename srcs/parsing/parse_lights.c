/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:42:29 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/27 14:39:09 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include <stdbool.h>

bool	parse_ambient_light(t_scene *scene)
{
	static bool	is_initialized = false;
	char		*part;

	if (is_initialized)
		return (false);
	is_initialized = true;
	part = ft_strtok(NULL, " \n");
	if (!is_float(part))
		return (false);
	scene->al_intensity = ft_atof(part);
	if (scene->al_intensity < 0.0f || scene->al_intensity > 1.0f)
		return (false);
	part = ft_strtok(NULL, " \n");
	scene->al_color = parse_color(part);
	if (scene->al_color == 0)
		return (false);
	part = ft_strtok(NULL, " \n");
	return (part == NULL);
}

bool	parse_light(t_scene *scene)
{
	static bool	is_initialized = false;
	char		*part;
	float		vect[3];

	if (is_initialized)
		return (false);
	is_initialized = true;
	part = ft_strtok(NULL, " \n");
	if (!parse_vector(part, vect, 0.0f, 0.0f))
		return (false);
	fill_vec(&scene->light.pos, vect[0], vect[1], vect[2]);
	part = ft_strtok(NULL, " \n");
	if (!is_float(part))
		return (false);
	scene->light.brightness = ft_atof(part);
	if (scene->light.brightness < 0.0f || scene->light.brightness > 1.0f)
		return (false);
	part = ft_strtok(NULL, " \n");
	scene->light.color = parse_color(part);
	if (scene->light.color == 0)
		return (false);
	part = ft_strtok(NULL, " \n");
	return (part == NULL);
}
