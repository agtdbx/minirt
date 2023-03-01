/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:42:29 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/01 18:50:07 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	parse_ambient_light(t_scene *scene)
{
	char	*part;

	if (scene->al_intensity != -1.0f)
		return (false);
	part = ft_strtok(NULL, " \n");
	if (part == NULL)
		return (false);
	if (!is_float(part))
		return (false);
	scene->al_intensity = ft_atof(part);
	if (scene->al_intensity < 0.0f || scene->al_intensity > 1.0f)
	{
		ft_printf_fd("Intensity of ambient light must be between 0 and 1\n", 2);
		return (false);
	}
	part = ft_strtok(NULL, " \n");
	if (part == NULL)
		return (false);
	scene->al_color = parse_color(part);
	if (scene->al_color == 0)
		return (false);
	part = ft_strtok(NULL, " \n");
	return (part == NULL);
}

bool	parse_light(t_scene *scene)
{
	char	*part;
	float	vect[3];

	if (scene->light.brightness != -1.0f)
		return (false);
	part = ft_strtok(NULL, " \n");
	if (part == NULL)
		return (false);
	if (!parse_vector(part, vect, 0.0f, 0.0f))
		return (false);
	scene->light.pos = create_vector(vect[0], vect[1], vect[2], false);
	part = ft_strtok(NULL, " \n");
	if (part == NULL)
		return (false);
	if (!is_float(part))
		return (false);
	scene->light.brightness = ft_atof(part);
	if (scene->light.brightness < 0.0f || scene->light.brightness > 1.0f)
	{
		ft_printf_fd("Intensity of ambient light must be between 0 and 1\n", 2);
		return (false);
	}
	part = ft_strtok(NULL, " \n");
	if (part == NULL)
		return (false);
	scene->light.color = parse_color(part);
	if (scene->light.color == 0)
		return (false);
	part = ft_strtok(NULL, " \n");
	return (part == NULL);
}
