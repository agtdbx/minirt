/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:42:29 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/27 16:08:29 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include <stdbool.h>

#include "libft.h"

static void		compute_intensity(t_light *ret_light);
static t_result	parse_brightness(char const *nptr, float *ret_brightness);

t_result	parse_ambient_light(t_scene *ret_scene)
{
	static bool	is_initialized = false;
	char		*tok;

	if (is_initialized)
		return (FAILURE);
	is_initialized = true;
	tok = ft_strtok(NULL, " \n");
	if (parse_brightness(tok, &ret_scene->ambient_light.brightness) == FAILURE)
		return (FAILURE);
	tok = ft_strtok(NULL, " \n");
	ret_scene->ambient_light.color = parse_color(tok);
	if (ret_scene->ambient_light.color == 0)
		return (FAILURE);
	tok = ft_strtok(NULL, " \n");
	if (tok != NULL)
		return (FAILURE);
	compute_intensity(&ret_scene->ambient_light);
	return (SUCCESS);
}

t_result	parse_light(t_scene *ret_scene)
{
	static bool	is_initialized = false;
	char		*tok;
	float		vect[3];

	if (is_initialized)
		return (FAILURE);
	is_initialized = true;
	tok = ft_strtok(NULL, " \n");
	if (!parse_vector(tok, vect, 0.0f, 0.0f))
		return (FAILURE);
	fill_vec(&ret_scene->light.pos, vect[0], vect[1], vect[2]);
	tok = ft_strtok(NULL, " \n");
	if (parse_brightness(tok, &ret_scene->light.brightness) == FAILURE)
		return (FAILURE);
	tok = ft_strtok(NULL, " \n");
	ret_scene->light.color = parse_color(tok);
	if (ret_scene->light.color == 0)
		return (FAILURE);
	tok = ft_strtok(NULL, " \n");
	if (tok != NULL)
		return (FAILURE);
	compute_intensity(&ret_scene->light);
	return (SUCCESS);
}

static t_result	parse_brightness(char const *nptr, float *ret_brightness)
{
	if (is_float(nptr) == false)
		return (FAILURE);
	*ret_brightness = ft_atof(nptr);
	if (*ret_brightness < 0.0f || 1.0f < *ret_brightness)
		return (FAILURE);
	return (SUCCESS);
}

static void	compute_intensity(t_light *ret_light)
{
	ret_light->intensity_r = (ret_light->color >> 24 & 0XFF) / 255.0f;
	ret_light->intensity_g = (ret_light->color >> 16 & 0XFF) / 255.0f;
	ret_light->intensity_b = (ret_light->color >> 8 & 0XFF) / 255.0f;
}
